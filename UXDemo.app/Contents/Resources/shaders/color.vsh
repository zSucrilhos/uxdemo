uniform mat4 projectionMatrix;
attribute vec4 position;

void main() {
    gl_Position = projectionMatrix * position;
}
