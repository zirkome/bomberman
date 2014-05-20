#version 120

///////////////////////////////
// Attributes coming from the vertex shader

varying vec4 fPosition;
varying vec4 fNormal;
varying vec2 fUv;
varying vec4 fColor;

///////////////////////////////
// Uniform variables

uniform sampler2D fTexture0;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void)
{
  vec4 texturePix = texture2D(fTexture0, fUv, -2);
  gl_FragData[0] = (fColor * texturePix);
  gl_FragData[1] = fPosition;
  gl_FragData[2] = fNormal;
}
