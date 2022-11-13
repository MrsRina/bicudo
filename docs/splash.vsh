void main() {
    gl_Position = MatrixProjection * vec4((VertexPosition * Rect.zw) + Rect.xy, Depth, 1);
    DataRect = Rect;
    TextureCoords = VertexTextureCoords;
}