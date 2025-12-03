import json

def get_base_scene():
    return {
        "camera": {
            "type": "perspective",
            "focal_length": 3,
            "eye": [0, 0.5, 6],
            "up": [0, 1, 0],
            "look": [0, 0, -1],
            "height": 1,
            "width": 1.7777777778
        },
        "materials": [
            # Added "km": [0,0,0] to all materials to prevent JSON errors
            {"name": "sky_blue", "ka": [0.4, 0.6, 1.0], "kd": [0.4, 0.6, 1.0], "ks": [0.0,0.0,0.0], "km": [0.0,0.0,0.0], "phong_exponent": 1},
            {"name": "grass", "ka": [0.2, 0.6, 0.2], "kd": [0.2, 0.6, 0.2], "ks": [0.0,0.0,0.0], "km": [0.0,0.0,0.0], "phong_exponent": 1},
            {"name": "bark", "ka": [0.4, 0.2, 0.1], "kd": [0.4, 0.2, 0.1], "ks": [0.0,0.0,0.0], "km": [0.0,0.0,0.0], "phong_exponent": 1},
            {"name": "leaves", "ka": [0.1, 0.5, 0.1], "kd": [0.1, 0.5, 0.1], "ks": [0.1,0.1,0.1], "km": [0.0,0.0,0.0], "phong_exponent": 10},
            {"name": "pika_yellow", "ka": [0.96, 0.82, 0.26], "kd": [0.96, 0.82, 0.26], "ks": [0.2,0.2,0.2], "km": [0.0,0.0,0.0], "phong_exponent": 20},
            {"name": "pika_red", "ka": [0.9, 0.2, 0.2], "kd": [0.9, 0.2, 0.2], "ks": [0.1,0.1,0.1], "km": [0.0,0.0,0.0], "phong_exponent": 10},
            {"name": "black", "ka": [0.05, 0.05, 0.05], "kd": [0.05, 0.05, 0.05], "ks": [0.3,0.3,0.3], "km": [0.0,0.0,0.0], "phong_exponent": 50},
            {"name": "eevee_brown", "ka": [0.6, 0.4, 0.2], "kd": [0.6, 0.4, 0.2], "ks": [0.1,0.1,0.1], "km": [0.0,0.0,0.0], "phong_exponent": 10},
            {"name": "cream", "ka": [0.95, 0.9, 0.8], "kd": [0.95, 0.9, 0.8], "ks": [0.1,0.1,0.1], "km": [0.0,0.0,0.0], "phong_exponent": 10}
        ],
        "lights": [
            {"type": "directional", "direction": [0.5, -0.8, -0.5], "color": [0.9, 0.9, 0.9]},
            {"type": "directional", "direction": [-0.5, 0, -0.2], "color": [0.3, 0.3, 0.3]}
        ],
        "objects": [
            {"type": "plane", "material": "grass", "point": [0, -0.5, 0], "normal": [0, 1, 0]},
            {"type": "plane", "material": "sky_blue", "point": [0, 0, -20], "normal": [0, 0, 1]}
        ]
    }

def add_sphere(scene, x, y, z, r, mat):
    scene["objects"].append({
        "type": "sphere", "material": mat, "center": [x, y, z], "radius": r
    })

def add_triangle(scene, p1, p2, p3, mat):
    scene["objects"].append({
        "type": "triangle", "material": mat, "corners": [p1, p2, p3]
    })

def build_scene():
    scene = get_base_scene()

    # TREE
    for i in range(5):
        add_sphere(scene, 0, -0.5 + i*0.3, -2, 0.3 - i*0.02, "bark")
    add_sphere(scene, 0, 1.2, -2, 1.0, "leaves")
    add_sphere(scene, 0.6, 1.0, -1.8, 0.7, "leaves")
    add_sphere(scene, -0.6, 1.1, -1.8, 0.7, "leaves")

    # PIKACHU 
    px, py, pz = -1.2, -0.2, 0
    add_sphere(scene, px, py, pz, 0.35, "pika_yellow")
    add_sphere(scene, px, py+0.45, pz, 0.3, "pika_yellow")
    add_triangle(scene, [px-0.2, py+0.6, pz], [px-0.5, py+1.0, pz], [px-0.1, py+0.7, pz+0.1], "pika_yellow")
    add_triangle(scene, [px+0.2, py+0.6, pz], [px+0.5, py+1.0, pz], [px+0.1, py+0.7, pz+0.1], "pika_yellow")
    add_sphere(scene, px-0.12, py+0.5, pz+0.25, 0.05, "black")
    add_sphere(scene, px+0.12, py+0.5, pz+0.25, 0.05, "black")
    add_sphere(scene, px-0.22, py+0.4, pz+0.1, 0.1, "pika_red")
    add_sphere(scene, px+0.22, py+0.4, pz+0.1, 0.1, "pika_red")
     # hands (front paws)
    add_sphere(scene, px-0.35, py+0.05, pz+0.06, 0.08, "pika_yellow")
    add_sphere(scene, px+0.35, py+0.05, pz+0.06, 0.08, "pika_yellow")
    # small thumb/pad details on hands
    add_sphere(scene, px-0.43, py+0.03, pz+0.02, 0.035, "black")
    add_sphere(scene, px+0.43, py+0.03, pz+0.02, 0.035, "black")

    # EEVEE
    ex, ey, ez = 1.2, -0.2, 0
    add_sphere(scene, ex, ey, ez, 0.35, "eevee_brown")
    add_sphere(scene, ex, ey+0.45, ez, 0.3, "eevee_brown")
    add_sphere(scene, ex+0.2, ey+0.2, ez+0.15, 0.12, "cream")
    add_sphere(scene, ex-0.2, ey+0.2, ez+0.15, 0.12, "cream")
    add_sphere(scene, ex, ey+0.15, ez+0.25, 0.12, "cream")
    add_triangle(scene, [ex-0.2, ey+0.6, ez], [ex-0.6, ey+0.9, ez+0.1], [ex-0.2, ey+0.7, ez-0.1], "eevee_brown")
    add_triangle(scene, [ex+0.2, ey+0.6, ez], [ex+0.6, ey+0.9, ez+0.1], [ex+0.2, ey+0.7, ez-0.1], "eevee_brown")
    add_sphere(scene, ex-0.12, ey+0.5, ez+0.25, 0.05, "black")
    add_sphere(scene, ex+0.12, ey+0.5, ez+0.25, 0.05, "black")
    # hands (front paws)
    add_sphere(scene, ex-0.35, ey+0.1, ez+0.06, 0.08, "eevee_brown")
    add_sphere(scene, ex+0.35, ey+0.1, ez+0.06, 0.08, "eevee_brown")
    # small thumb/pad details on hands
    add_sphere(scene, ex-0.43, ey+0.09, ez+0.02, 0.035, "cream")
    add_sphere(scene, ex+0.43, ey+0.09, ez+0.02, 0.035, "cream")

    return scene

if __name__ == "__main__":
    with open("src/showcase.json", "w") as f:
        json.dump(build_scene(), f, indent=2)
    print("Success! Created showcase.json with fixed materials.")