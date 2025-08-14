#include <stdlib.h>
#include <camera.h>
#include <vmm/projection.h>

Camera *camera_create(Window *win, CameraType type, Camera_Args args) {
    Camera *c = calloc(1, sizeof(Camera));
    c->type = type;
    c->position = (Vector3){0};
    if(type == ORTHOGRAPHIC_CAMERA) {
        c->camera_o.min = (Vector2){args.min_max.x, args.min_max.y};
        c->camera_o.max = (Vector2){args.min_max.z, args.min_max.w};
        c->view_proj.proj = mat4_orthogonal(c->camera_o.min.x, c->camera_o.max.x, c->camera_o.min.y, c->camera_o.max.y, -1, 1);

        Vector3 eye = (Vector3){0, 0, 1};
        Vector3 center = (Vector3){0, 0, 0};
        Vector3 up = (Vector3){0, 1, 0};
        c->view_proj.view = mat4_look_at(eye, center, up);
    }
    else if(type == PERSPECTIVE_CAMERA) {
        c->camera_p.fov = args.p_fov;
        c->camera_p.aspect = win->settings.size.x / win->settings.size.y;
        c->camera_p.zNear = 0.01f;
        c->camera_p.zFar = 1000.0f;
        c->camera_p.direction = (Vector3){0.0f, 0.0f, -1.0f};
        c->camera_p.up = (Vector3){0.0f, 1.0f, 0.0f};
        c->camera_p.right = vec3_cross(c->camera_p.direction, c->camera_p.up);
        c->view_proj.proj = mat4_perspective(c->camera_p.fov, c->camera_p.aspect, c->camera_p.zNear, c->camera_p.zFar);
        
        Vector3 eye = (Vector3){0, 0, 0};
        Vector3 center = vec3_add(eye, c->camera_p.direction);
        Vector3 up = c->camera_p.up;
        c->view_proj.view = mat4_look_at(eye, center, up);
    }
    return c;
}