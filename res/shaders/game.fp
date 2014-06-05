#version 120

///////////////////////////////
// Structures

struct light
{
  vec4 position;
  vec4 diffuse;
  vec4 specular;
  vec2 attenuation; // x = start, y = end

  float spotCutoff, spotExponent;
  vec3 spotDirection;

  float shado;
};

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 camPos;
uniform vec4 ambientLight;

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec4 fPosition;
varying vec4 fNormal;
varying vec2 fUv;

vec4 CalcLight(light currlight, vec3 normal, vec3 position);
float smoothstep(float edge0, float edge1, float x);

void main(void)
{
  vec4 color = texture2D(fTexture0, fUv) * fColor;
  vec4 position = fPosition;
  vec4 normal = fNormal;

  vec4 lighting = ambientLight;

  light tmpLight;

  tmpLight.position = vec4(0, 0.7, 0.3, 0.0);
  tmpLight.diffuse = vec4(1, 1, 1, 0);
  tmpLight.specular = vec4(2, 2, 2, 0);
  tmpLight.spotCutoff = 180;

  if (lighting != vec4(1.0f, 1.0f, 1.0f, 1.0f))
    lighting += CalcLight(tmpLight, normal.xyz, position.xyz);

  gl_FragColor = color * lighting;
}

float smoothstep(float edge0, float edge1, float x)
{
  if (x <= edge0)
    return 0.0;
  else if (x >= edge1)
    return 1.0;
  else
    {
      float t = (x - edge0) / (edge1 - edge0);
      return 3.0 * pow(t, 3) - 2.0 * pow(t, 2);
    }
}

vec4 CalcLight(light currlight, vec3 normal, vec3 position)
{
  vec3 lightDirection;
  float attenuation;

  if (currlight.position.w == 0.0) // directional light?
    {
      attenuation = 1.0; // no attenuation
      lightDirection = normalize(vec3(currlight.position));
    }
  else // point light or spotlight (or other kind of light)
    {
      vec3 positionToLightSource = vec3(currlight.position - vec4(position, 0.0));
      float distance = length(positionToLightSource);
      lightDirection = normalize(positionToLightSource);
      attenuation = smoothstep(currlight.attenuation.y, currlight.attenuation.x, distance);

      if (currlight.spotCutoff <= 90.0) // spotlight?
        {
          float clampedCosine = max(0.0, dot(-lightDirection, normalize(currlight.spotDirection)));

          if (clampedCosine < cos(radians(currlight.spotCutoff))) // outside of spotlight cone?
            attenuation = 0.0;
          else
            attenuation = attenuation * pow(clampedCosine, currlight.spotExponent);
        }
    }

  vec3 diffuseReflection = attenuation * vec3(currlight.diffuse) * max(0.0, dot(normal, lightDirection));

  vec3 specularReflection = vec3(0.0, 0.0, 0.0);
  float lambertTerm = max(dot(normal, lightDirection), 0.0);
  if (lambertTerm > 0.0) //light source on the right side
    {
      specularReflection = attenuation * vec3(currlight.specular) * pow(max(0.0, dot(reflect(-lightDirection, normal), normalize(camPos - position))), 5);
    }

  return vec4((diffuseReflection + specularReflection), 0.0);
}
