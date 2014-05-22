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
  vec4 color = (fColor * texturePix);
  gl_FragData[0] = color;
  gl_FragData[1] = vec4(fPosition.xyz, color.w);
  gl_FragData[2] = vec4(fNormal.xyz, color.w);
}
