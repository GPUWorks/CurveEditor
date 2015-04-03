# CurveEditor
A curve editor using OpenGL supporting different types of curves

This curve editor was a midterm project for my Graphics class that essentially creates a design editor that allows a user to create shapes using different types of curves using only keyboard and mouse.

To use:
    Press and hold down the keys listed below and click points in the window to create curves or use other functional keys

Implemented Items:
    Curves:
        - P Polyline
        - B Bezier
        - L Lagrange
        - C Catmull-Clark Subdivision (default set to 3 subdivisions - changeable as global variable)

    Functional Keys:
        - SPACE selects the next curve
        - F fills in (convex) curves
        - D deletes control points
        - A adds control points
        - Z clears all the curves on the screen

    Other Functionalities:
        - Curve selection
            (doesn't work amazingly well for Polyline and Subdivision)
        - Control point dragging
        - Curve dragging

    Total: 85/85 Points

Thank you again for the extra time.
