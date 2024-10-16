#include "utils.h"
#include "buildings.h"



GameState::GameState() : toggleFence(false), itemActive(0), fence(new Fence), pens() {
    // The unique_ptrs will automatically handle memory management
}


float lerp_to(float position, float target, float rate) {
    return position + (target - position) * rate;  // Lerp between position and target
}

vec3 lerp3D(vec3 position, vec3 target, float rate) {
    return position + (target - position) * rate;  // Lerp between vec3 position and target
}

float GetRandomFloat(float min, float max) {
    return min + (max - min) * ((float)GetRandomValue(0, RAND_MAX) / (float)RAND_MAX);
}

// Helper function to get the closest point on a line segment to a point
vec3 GetClosestPointOnLineFromPoint(vec3 point, vec3 lineStart, vec3 lineEnd) {
    vec3 line = Vector3Subtract(lineEnd, lineStart);
    float lineLength = Vector3Length(line);
    vec3 lineNormalized = Vector3Scale(line, 1.0f / lineLength);

    float t = Vector3DotProduct(Vector3Subtract(point, lineStart), lineNormalized);
    t = Clamp(t, 0, lineLength);

    return Vector3Add(lineStart, Vector3Scale(lineNormalized, t));
}

// Helper function to check collision between a point and a line segment
bool CheckCollisionPointLine(vec3 point, vec3 lineStart, vec3 lineEnd, float threshold) {
    vec3 closest = GetClosestPointOnLineFromPoint(point, lineStart, lineEnd);
    return Vector3Distance(point, closest) <= threshold;
}

vec3 vec2to3(vec2 vec2, float y) {
    return vec3{vec2.x, y, vec2.y};
}


vec2 project_mouse(float y, Camera3D camera) {
    Vector2 mousePos = GetMousePosition();
    Ray ray = GetMouseRay(mousePos, camera);

    // Check if the ray intersects the ground (y = 0 plane)
    if (ray.direction.y != 0) { // Prevent division by zero
        float t = (1.0f - ray.position.y) / ray.direction.y; // Calculate parameter t for y = 1.0
        if (t >= 0) { // Ensure the intersection is in front of the camera
            vec2 intersection = {
                ray.position.x + ray.direction.x * t,
                ray.position.z + ray.direction.z * t
            };
            return intersection;
        }
    }
}
