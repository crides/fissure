import cadquery as cq
import math

ball_r = 34 / 2
gap_r = 1
wall_t = 3
bear_r = 4.3 / 2
lens_dist = 2.4
pcb_lens_dist = 2

ball_out_r = ball_r + bear_r
bottom = ball_r + lens_dist + pcb_lens_dist

def polar(r, theta, phi):
    xy = math.sin(phi) * r
    return cq.Vector(xy * math.cos(theta), xy * math.sin(theta), math.cos(phi) * r)

# pts = [polar(59/2, math.radians(t + p), math.radians(p)) for t in [0, 120, 240] for p in [60, 120]]
phis = list(map(math.radians, [75, 120]))
pts = [polar(ball_out_r, math.radians(t * 90 + (1-p) * 45), phis[p]) for t in range(4) for p in range(2)]
# print(pts)
bears = (cq.Workplane()
         .transformed(offset=(0, 0, bottom))
         .pushPoints(pts)
         .sphere(bear_r))
top_slice = polar(ball_out_r, 0, min(phis)).z + bear_r
cross = cq.Workplane().box(100, ball_out_r * 2 / 3, 100, centered=(True, True, False))
cross = cross + cross.rotateAboutCenter((0, 0, 1), 90)
holder = (cq.Workplane()
          .sphere(ball_out_r + wall_t)
          .transformed(offset=(0, 0, -bottom))
          .cylinder(bottom, ball_out_r + wall_t, centered=(True, True, False))
          .cut(cq.Workplane().sphere(ball_out_r).cut(cq.Workplane().transformed(offset=(0, 0, top_slice)).box(100, 100, 100, centered=(True, True, False))))
          .cut(cq.Workplane().transformed(offset=(0, 0, top_slice + 1)).box(100, 100, 100, centered=(True, True, False)))
          .cut(bears)
          .cut(cq.Workplane().sphere(ball_r + 0.5))
          .cut(cross)
          .cut(cq.Workplane().transformed(offset=(0, 0, -bottom)).circle(100).extrude(-10))
          .faces("<Z").workplane()
          .rect(9, 17).extrude(-pcb_lens_dist, combine="s")  # TODO actual size and location
          .slot2D(9, 6, 90).cutThruAll() # TODO actual size and location
          .faces("<Z[2]")
          .workplane(offset=-ball_r * 0.35)
          .split(keepTop=True, keepBottom=True)
          )
holder_top = holder.solids(">Z")
holder_bot = holder.solids("<Z")

inner_r = min([e.BoundingBox().xlen for e in holder_bot.faces(">Z").edges("%circle").vals()]) / 2
holder_bot = holder_bot.intersect(cq.Workplane().cylinder(100, inner_r + wall_t))
bot_h = holder_bot.val().BoundingBox().zlen
top_inner_r = inner_r + wall_t + gap_r
top_shroud = holder_bot.faces("<Z").workplane().circle(top_inner_r + wall_t).circle(top_inner_r).extrude(-bot_h, combine=False)
holder_top = holder_top.faces("<Z").wires().toPending().cutBlind(wall_t)
bot_wires = sorted(top_shroud.faces(">Z").wires().vals(), key=lambda e: e.BoundingBox().xlen)
top_wires = sorted(holder_top.faces("<Z").wires().vals(), key=lambda e: e.BoundingBox().xlen)
adapter = cq.Workplane().add(cq.Solid.makeLoft([top_wires[1], bot_wires[1]])).cut(cq.Solid.makeLoft([top_wires[0], bot_wires[0]]))
holder_top += adapter + top_shroud
holder_top = holder_top.translate((0, 0, bottom)) + cq.Workplane().rarray(41, 28.8, 2, 2).cylinder(7, 3, centered=(True, True, False)) - cq.Workplane().rarray(41, 28.8, 2, 2).cylinder(5, 3.5 / 2, centered=(True, True, False))
bot_holes = [(-15, 0), (15, 0), (0, 15), (0, -15)]
holder_bot = holder_bot.translate((0, 0, bottom)) + cq.Workplane().pushPoints(bot_holes).cylinder(7, 3, centered=(True, True, False)) - cq.Workplane().pushPoints(bot_holes).cylinder(5, 3.5 / 2, centered=(True, True, False))

ball = cq.Workplane().sphere(ball_r).translate((0, 0, bottom))

whole = (cq.Assembly()
         .add(holder_top, name="holder_top")
         .add(holder_bot, name="holder_bot")
         .add(bears, name="bearings", color=cq.Color("gray"))
         .add(ball, name="ball", color=cq.Color("lightgray"))
         )
show_object(whole)
whole.save("trackball.step")
# show_object(bears)
