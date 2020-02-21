//#include "LetsDrawSomeStuff.h"
//
////number of possible lights
//#define MAX_LIGHTS 10
//
////types of lights to be called by switch statement
//#define DIRECTIONAL_LIGHT 0
//#define POINT_LIGHT 1
//#define SPOT_LIGHT 2
//
//
////base light
//struct Light
//{
//	//where light is located
//	Vertex Position;
//	Vertex Direction;
//
//	float Angle;
//	float ConstAttenuation;
//	float LinearAttenuation;
//	float QuadraticAttenuation;
//
//	Vertex ambient;
//	Vertex diffuse;
//	Vertex specular;
//	Vertex Color;
//
//	int LightType;
//	bool Enabled;
//	int Padding;
//};
//
////material struct will add light effect to the objects
//struct Material
//{
//	float Ambient;
//	float Diffuse;
//	float Specular;
//
//	float SpecularPower;
//	bool Texture;
//	float padding;
//};
//
//struct MaterialProperties
//{
//	Material _materialProperties;
//};
//
//struct LightType
//{
//	Vertex Diffuse;
//	Vertex Specular;
//};
//
//struct LightProperties
//{
//	Vertex EyePosition;
//	Vertex GlobalAmbient;
//	Light Lights[MAX_LIGHTS];
//};
//
//LightProperties lightProperties;
//
//class Lighting
//{
//
//	Vertex Diffuse(Light light, Vertex source, Vertex norm);
//	Vertex Specular(Light light, Vertex view, Vertex source, Vertex norm);
//	float Attenuation(Light light, float distance);
//	LightType PointLight(Light light, Vertex view, Vertex point, Vertex norm);
//	LightType DirectionalLight(Light light, Vertex view, Vertex direction, Vertex norm);
//	float SpotCone(Light light, Vertex direction);
//	LightType SpotLight(Light light, Vertex view, Vertex point, Vertex norm);
//	LightType MakeLight(Vertex point, Vertex norm);
//	//Vertex TextureLight_PixelShader(PixelShader);
//
//	//basic light variables
//	//Vertex LightColor = { 1.0f, 1.0f, 1.0f };
//	//Vertex LightPos = { 1.0f, 0.5f, 0.0f };
//	//Light BaseLight;
//	//
//	//Material object;
//	//
//	//float ambientLightStrength = 0.1;
//
//
//
//	//void SetDirectionalLight();
//
//
//	//Material SetMaterial(DirectionalLight light, Material object, Vertex Normal);
//	//Vertex SetDirLight(DirectionalLight Light, Vertex normal, Vertex viewDirection);
//
//};
//
//Vertex Lighting::Diffuse(Light light, Vertex source, Vertex norm)
//{
//	float diff = maxf(0, DotProduct(norm, source));
//	Vertex diffuse = Multiply_VertexxVertex(light.Color, diffuse);
//	return diffuse;
//}
//
//Vertex Lighting::Specular(Light light, Vertex view, Vertex source, Vertex norm)
//{
//	//phong
//	float reflection = Normalize(reflect(-source, norm));
//	float refl = maxf(0.0f, DotProduct(reflection, view));
//
//	//blinn phong
//	float bp = Normalize(reflect(-(source), norm));
//	float bplight = maxf(0.0f, DotProduct(norm, bp));
//
//	Vertex specular = light.Color * pow(refl, Material.SpecularPower);
//}
//
//float Lighting::Attenuation(Light light, float distance)
//{
//	float attenuation = 1.0f / ((light.ConstAttenuation + light.LinearAttenuation * distance + light.QuadraticAttenuation * distance) * distance);
//	return attenuation;
//}
//
//LightType Lighting::PointLight(Light light, Vertex view, Vertex point, Vertex norm)
//{
//	LightType pointLight;
//
//	Vertex l = (Subtract_VertexxVertex(light.Position, point));
//	float distance = maxf(l);
//	l = Divide_VertexxFloat(l, distance);
//
//	float attenuation = Attenuation(light, distance);
//
//	pointLight.Diffuse = Multiply_VertexxFloat(Diffuse(light, l, norm), attenuation);
//	pointLight.Specular = Multiply_VertexxFloat(Specular(light, view, l, norm), attenuation);
//
//	return pointLight;
//
//}
//
//LightType Lighting::DirectionalLight(Light light, Vertex view, Vertex direction, Vertex norm)
//{
//	LightType directionalLight;
//
//	Vertex l;
//	l.xyzw[1] = -light.Direction.xyzw[1];
//	l.xyzw[2] = -light.Direction.xyzw[2];
//	l.xyzw[3] = -light.Direction.xyzw[3];
//
//	directionalLight.Diffuse = Diffuse(light, l, norm);
//	directionalLight.Specular = Specular(light, view, l, norm);
//
//	return directionalLight;
//}
//
//float Lighting::SpotCone(Light light, Vertex direction)
//{
//	float CosMin = cos(light.Angle);
//	float CosMax = (CosMin + 1.0f) / 2.0f;
//	float CosAngle = DotProduct(light.Direction, (-direction.xyzw[1], -direction.xyzw[2], -direction.xyzw[3]));
//
//	float spotCone = smoothstep{ CosMin, CosMax, CosAngle };
//	return spotCone;
//}
//
//LightType Lighting::SpotLight(Light light, Vertex view, Vertex point, Vertex norm)
//{
//	LightType spotLight;
//
//	Vertex l = (Subtract_VertexVertex(light.Position, point));
//	float distance = maxf(l);
//	l = Divide_VertexxFloat(l, distance);
//
//	float attenuation = Attenuation(light, distance);
//	float spotIntensity = SpotCone(light, l);
//
//	spotLight.Diffuse = Multiply_VertexxFloat(Diffuse(light, l, norm), attenuation);
//	spotLight.Specular = Multiply_VertexxFloat(Specular(light, view, l, norm), attenuation);
//}
//
//LightType Lighting::MakeLight(Vertex point, Vertex norm)
//{
//	Vertex view = Normalize(lightProperties.EyePosition - point);
//	LightType LightResult = { {0, 0, 0}, {0, 0, 0} };
//
//	for (int lights = 0; lights < MAX_LIGHTS; ++lights)
//	{
//		LightType type = { {0, 0, 0}, {0, 0, 0} };
//
//		if (!lightProperties.Lights[lights].Enabled)
//			continue;
//
//		switch (lightProperties.Lights[lights].LightType)
//		{
//		case DIRECTIONAL_LIGHT:
//		{
//			type = DirectionalLight(lightProperties.Lights[lights], view, point, norm);
//		}
//		break;
//		case POINT_LIGHT:
//		{
//			type = PointLight(lightProperties.Lights[lights], view, point, norm);
//		}
//		break;
//		case SPOT_LIGHT:
//		{
//			type = SpotLight(lightProperties.Lights[lights], view, point, norm);
//		}
//		break;
//		}
//
//		LightResult.Diffuse = Add_VertexxVertex(LightResult.Diffuse, type.Diffuse);
//		LightResult.Specular = Add_VertexxVertex(LightResult.Specular, type.Specular);
//
//	}
//
//	return LightResult;
//
//}
//
//Material Lighting::SetMaterial(DirectionalLight light, Material object, Vertex Normal)
//{
//	//set ambient
//	Vertex = Multiply_VertexxVertex(BaseLight.Color, object.ambient);
//
//	//diffuse
//	Vertex normal = Normalize(Normal);
//	float diff = maxf(DotProduct(normal, DirLight.direction), 0.0f);
//	Vertex diffuse = LightColor * (Multiply_VertexxFloat(diff, object.diffuse));
//
//	//
//	Vertex viewDirection = Normalize(viewPosition - FragPosition); //viewpoition with be gather from world matrix
//}
//Vertex SetDirLight(DirectionalLight Light, Vertex normal, Vertex viewDirection)
//{
//	Vertex lightDirection = Normalize(-Light.direction));
//
//	//diffuse shading
//	float diff = max(dot(normal, lightDirection), 0.0);
//
//	//specular shading
//	Vertex reflectDirection = reflect(-lightDir, normal);
//	float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
//}