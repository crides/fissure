from kicaq import *
import cadquery as cq

# params

# consts
sw_w = 14
sw_pc = 15
sw_fr = 1
sw_tabh = 2
m2_dia = 2
nut_h = 1.5
nut_dia = 6.2
edge_top_h = 4.5
bot_h = 3
sk_top_h = 9
pcb_thik = 1.6
sk_cl = 0.2
sk_w = 1
edge_sk_w = sk_cl + sk_w
tab_l = (sw_pc - sw_w) / 2

board = Board("pcb/fissure/fissure.kicad_pcb")

l_mid_k, r_mid_k = board.pos("K8"), board.pos("K28")
l_mid_col = cq.Sketch().push([l_mid_k]).rect(sw_w, sw_pc * 3 - tab_l * 2)#.reset().vertices("<Y").fillet(sw_fr)

l_ring_k = board.pos("K7")
l_ind_k = board.pos("K9")
l_side_cols = cq.Sketch().push([l_ind_k, l_ring_k]).rect(sw_w, sw_pc * 3 - tab_l * 2)#.reset().vertices(">Y").fillet(sw_fr)

l_pink_k = board.pos("K6")    # random for easy
l_ring_bot = l_ring_k[1] - 1.5 * sw_pc + tab_l
l_pink_top = l_pink_k[1] + 1.5 * sw_pc - tab_l
l_pink_clus = (cq.Sketch()
             # .push([(l_pink_k[0] - sw_pc / 2, l_pink_k[1] - 0.5)]).rect(sw_pc * 2 - 1, sw_pc * 3)
             .push([(l_pink_k[0] - sw_pc / 2, l_pink_k[1] + sw_pc / 2)]).rect(sw_pc * 2 - tab_l * 2, sw_pc * 2 - tab_l * 2)
             .push([(l_pink_k[0], l_pink_k[1] - sw_pc)]).rect(sw_w, sw_w)
             .push([(l_pink_k[0], l_pink_k[1] - sw_pc / 2)]).rect(sw_w, tab_l * 2)
             .push([(l_pink_k[0] + sw_pc / 2, (l_ring_bot + l_pink_top) / 2)]).rect(tab_l * 2, l_pink_top - l_ring_bot)
             #.reset().vertices("<Y").fillet(sw_fr)
             )

l_ind_out_k = board.pos("K10")
# compensate for ind tab, but leave for right tab
l_in_bot = l_ind_k[1] - 1.5 * sw_pc + tab_l
l_out_top = l_ind_out_k[1] + 1.5 * sw_pc - tab_l
l_ind_out = (cq.Sketch()
           .push([l_ind_out_k]).rect(sw_w, sw_pc * 3 - tab_l * 2)
           .push([(l_ind_k[0] + sw_pc / 2, (l_in_bot + l_out_top) / 2)]).rect(tab_l * 2, l_out_top - l_in_bot)
           #.reset().vertices("<Y").fillet(sw_fr)
           )

mounts = [board.pos(fp) for fp in board.fps() if fp.GetFPIDAsString() == "soldered-nuts:M2"]

bs = cq.Workplane().add(board.edges()).extrude(edge_top_h)
lalf_b, ralf_b = bs.solids(">Y"), bs.solids(">X")
ralf_left = ralf_b.edges("<X").val().Center().x
lalf_right = lalf_b.edges(">X").val().Center().x
mirror = lambda l: l.mirror("YZ", ((ralf_left + lalf_right) / 2, 0))
ralf_b = mirror(lalf_b)
comp_hole = cq.Workplane().placeSketch(board.layer(pcbnew.User_2)).extrude(3.5)
lalf_w, ralf_w = lalf_b.wires("<Z"), ralf_b.wires("<Z")
lalf_edge = lalf_w.toPending().extrude(edge_top_h + pcb_thik + bot_h).faces("|Z").shell(edge_sk_w).translate((0, 0, - pcb_thik - bot_h))
sk_sk = lambda: board.layer(pcbnew.User_1).reset().vertices().fillet(sw_fr)
sks = cq.Workplane().placeSketch(sk_sk().reset().wires().offset(sk_cl + sk_w)).extrude(sk_top_h) - cq.Workplane().placeSketch(sk_sk().reset().wires().offset(sk_cl)).extrude(sk_top_h)
l_base = lalf_b.add([l_mid_col, l_side_cols, l_pink_clus, l_ind_out]).cutThruAll() + lalf_edge
lalf = l_base + sks.solids("<X") - comp_hole.intersect(lalf_b)
ralf = mirror(l_base) + sks.solids(">X") - comp_hole.intersect(ralf_b) - cq.Workplane().placeSketch(board.layer(pcbnew.User_4)).extrude(-10)

lcon, rcon = board.pos("J3"), board.pos("J12")

lalf_bot = (lalf_w.toPending().extrude(-bot_h, combine=False) - cq.Workplane().transformed(offset=lcon).box(4.6, 100, 10)).solids("<X").faces(">Z").workplane()
ralf_bot = (ralf_w.toPending().extrude(-bot_h, combine=False) - cq.Workplane().transformed(offset=rcon).box(4.6, 100, 10)).solids(">X").faces(">Z").workplane()

for mount in mounts:
    lalf -= cq.Workplane().transformed(offset=mount).cylinder(nut_h + 0.5, nut_dia / 2, centered=(True, True, False))
    ralf -= cq.Workplane().transformed(offset=mount).cylinder(nut_h + 0.5, nut_dia / 2, centered=(True, True, False))
    lalf_bot -= cq.Workplane().transformed(offset=mount).cylinder(10, m2_dia / 2)
    ralf_bot -= cq.Workplane().transformed(offset=mount).cylinder(10, m2_dia / 2)

for i in range(1, 21):
    sw = board.fp(f"K{i}")
    lalf -= cq.Workplane().box(sw_pc + sk_cl * 2, sw_pc + sk_cl * 2, 10, centered=(True, True, False)).translate((*board.pos(sw), sw_tabh))
    for p in sw.Pads():
        lalf_bot -= cq.Workplane().transformed(offset=(*board.p(p.GetPosition()), -2)).cylinder(2, p.GetSizeX() / 2 / 1000000 + 0.5, centered=(True, True, False))

for i in range(21, 41):
    sw = board.fp(f"K{i}")
    ralf -= cq.Workplane().box(sw_pc + sk_cl * 2, sw_pc + sk_cl * 2, 10, centered=(True, True, False)).translate((*board.pos(sw), sw_tabh))
    for p in sw.Pads():
        ralf_bot -= cq.Workplane().transformed(offset=(*board.p(p.GetPosition()), -2)).cylinder(2, p.GetSizeX() / 2 / 1000000 + 0.5, centered=(True, True, False))

usbc = cq.importers.importStep(board.trans_model_path(board.fp("J2").Models()[0].m_Filename))
usbc_hole = usbc.faces("<Y").wires(cq.selectors.AreaNthSelector(-1)).toPending().workplane().extrude(10, both=True, combine=False)

lalf -= cq.Workplane().add(usbc_hole).rotate((0,0,0), (0,0,1), 180).translate(board.pos("J2"))
ralf -= cq.Workplane().add(usbc_hole).rotate((0,0,0), (0,0,1), 180).translate(board.pos("J8"))

lalf -= cq.Workplane().box(6, 5, 3).translate((board.pos("SW4")[0], lalf_b.edges(">Y").val().Center().y, 0.5))
lalf -= cq.Workplane().pushPoints([board.pos("D1")]).cylinder(10, 1)
lalf -= cq.Workplane().placeSketch(board.layer(pcbnew.User_3)).extrude(10)

ralf -= cq.Workplane().box(6, 5, 3).translate((board.pos("SW3")[0], lalf_b.edges(">Y").val().Center().y, 0.5))
ralf -= cq.Workplane().pushPoints([board.pos("D2")]).cylinder(10, 1)
ralf -= cq.Workplane().placeSketch(board.layer(pcbnew.User_3)).extrude(10)

lalf_bot = lalf_bot.transformed(offset=(l_mid_k[0], lcon[1], -bot_h)).circle(8).circle(9 / 2).extrude(-8).translate((0, 0, -pcb_thik))
ralf_bot = ralf_bot.transformed(offset=(r_mid_k[0], rcon[1], -bot_h)).circle(8).circle(9 / 2).extrude(-8).translate((0, 0, -pcb_thik))

cq.exporters.export(lalf, "pcb/fissure/left-case.step")
cq.exporters.export(lalf_bot, "pcb/fissure/left-case-bot.step")
cq.exporters.export(ralf, "pcb/fissure/right-case.step")
cq.exporters.export(ralf_bot, "pcb/fissure/right-case-bot.step")

if "show_object" in locals():
    show_object(lalf)
    show_object(lalf_bot)
    show_object(ralf)
    show_object(ralf_bot)
