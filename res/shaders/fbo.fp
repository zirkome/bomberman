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
 if (texture2D(fTexture0, fUv, -2).w > 0.5)
  gl_FragData[0] = fColor * texture2D(fTexture0, fUv, -2);
 else
  gl_FragData[0] = vec4(1.0, 1.0, 1.0, 0.0);
  gl_FragData[1] = fPosition;
  gl_FragData[2] = fNormal;
}
