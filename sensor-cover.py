from build123d import *

x, y = 7 * 2, 10.5 * 2
b = Box(x, y, 6, align=(Align.CENTER, Align.CENTER, Align.MIN))
shell = offset(b, 2, b.faces() << Axis.Z)
# shell = Solid(b).offset_3d([b.faces().sort_by(Axis.Z).first], 2)
# shell = offset(b, 2, b.faces().sort_by(Axis.Z).first)
base = Rectangle(31.2 + 3 * 2, 23 + 3 * 2)
base = fillet(base.vertices(), 4)
base = extrude(base - GridLocations(31.2, 23, 2, 2) * Circle(2.2 / 2) - Rectangle(x, y), 2)
whole = shell + base

show_object(whole)
whole.export_step("sensor-cover.step")
