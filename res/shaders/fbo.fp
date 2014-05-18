#version 120

///////////////////////////////
// Attributes coming from the vertex shader

in vec4 fPosition;
in vec4 fNormal;
in vec2 fUv;
in vec4 fColor;

///////////////////////////////
// Uniform variables

uniform sampler2D fTexture0;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main( void )
{
  gl_FragData[0] = vec4(fColor * (texture2D(fTexture0, fUv, -2).rgb), 1.0);
  gl_FragData[1] = vec4(fPosition, 0.0);
  gl_FragData[2] = vec4(fNormal, 0);
}
