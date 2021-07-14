from build123d import *

y = 10.3 * 2
b = Box(y, y, 6, align=(Align.CENTER, Align.CENTER, Align.MIN))
shell = offset(b, 2, b.faces() << Axis.Z)
# shell = Solid(b).offset_3d([b.faces().sort_by(Axis.Z).first], 2)
# shell = offset(b, 2, b.faces().sort_by(Axis.Z).first)
base = extrude(Circle(19) - PolarLocations(15, 4) * Circle(2.2 / 2) - Rectangle(y, y), 2)
whole = shell + base

show_object(whole)
whole.export_step("sensor-cover.step")
