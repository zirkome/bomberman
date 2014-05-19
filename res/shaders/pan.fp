#version 120

///////////////////////////////
// Attributes coming from the vertex shader

varying vec2 fUv;

///////////////////////////////
// Uniform variables

uniform sampler2D tColor;
uniform sampler2D tPosition;
uniform sampler2D tNormals;

void main(void)
{
  vec4 color = texture2D(tColor, fUv);
  vec4 position = texture2D(tPosition, fUv);
  vec4 normal = texture2D(tNormals, fUv);

  normal = normalize(normal);

  gl_FragColor = color;
}
