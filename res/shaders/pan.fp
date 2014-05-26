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

///////////////////////////////
// Attributes coming from the vertex shader

varying vec2 fUv;

///////////////////////////////
// Uniform variables

uniform sampler2D tColor;
uniform sampler2D tPosition;
uniform sampler2D tNormals;

uniform vec3 camPos;

vec4 CalcLight(light currlight, vec3 normal, vec3 position);

void main(void)
{
  vec4 color = texture2D(tColor, fUv);
  vec4 position = texture2D(tPosition, fUv);
  vec4 normal = texture2D(tNormals, fUv);

  normal = normalize(normal);

  vec4 lighting = vec4(0.005, 0.005, 0.005, 1.0);

  light tmpLight;

  tmpLight.position = vec4(5, 5, 5, 1);
  tmpLight.diffuse = vec4(0.8, 0.8, 0.8, 0);
  tmpLight.specular = vec4(1, 1, 1, 0);
  tmpLight.spotCutoff = 180;

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
            {
              attenuation = 0.0;
            }
          else
            {
              attenuation = attenuation * pow(clampedCosine, currlight.spotExponent);
            }
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

