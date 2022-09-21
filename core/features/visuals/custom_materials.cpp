#include "../../../dependencies/utilities/csgo.hpp"
#include "../features.hpp"

// custom materials for chams

void visuals::custom_materials()
{
	// adv. regular

	std::ofstream("csgo\\materials\\onetap_overlay.vmt") << R"#("VertexLitGeneric"
    {
			"$basetexture"				    "vgui/white"
            "$ignorez"      "0"
			"$envmap"						"env_cubemap"
			"$envmaptint"                   "[.10 .10 .10]"
			"$pearlescent"					"0"
			"$phong"						"1"
			"$phongexponent"				"10"
			"$phongboost"					"1.0"
			"$rimlight"					    "1"
			"$rimlightexponent"		        "1"
			"$rimlightboost"		        "1"
			"$model"						"1"
			"$nocull"						"0"
			"$halflambert"				    "1"
			"$lightwarptexture"             "metalic"
    })#";

	std::ofstream("csgo\\materials\\onetap_overlay_xqz.vmt") << R"#("VertexLitGeneric"
    {
			"$basetexture"				    "vgui/white"
            "$ignorez"      "1"
			"$envmap"						"env_cubemap"
			"$envmaptint"                   "[.10 .10 .10]"
			"$pearlescent"					"0"
			"$phong"						"1"
			"$phongexponent"				"10"
			"$phongboost"					"1.0"
			"$rimlight"					    "1"
			"$rimlightexponent"		        "1"
			"$rimlightboost"		        "1"
			"$model"						"1"
			"$nocull"						"0"
			"$halflambert"				    "1"
			"$lightwarptexture"             "metalic"
    })#";

	// flat

	std::ofstream("csgo\\materials\\flat.vmt") << R"#("UnlitGeneric"
	{
	  "$basetexture" "vgui/white"
	  "$ignorez"      "0"
	  "$envmap"       ""
	  "$nofog"        "1"
	  "$model"        "1"
	  "$nocull"       "0"
	  "$selfillum"    "1"
	  "$halflambert"  "1"
	  "$znearer"      "0"
	  "$flat"         "1"
	})#";

	std::ofstream("csgo\\materials\\flat_xqz.vmt") << R"#("UnlitGeneric"
	{
	  "$basetexture" "vgui/white"
	  "$ignorez"      "1"
	  "$envmap"       ""
	  "$nofog"        "1"
	  "$model"        "1"
	  "$nocull"       "0"
	  "$selfillum"    "1"
	  "$halflambert"  "1"
	  "$znearer"      "0"
	  "$flat"         "1"
	})#";

	// regular

	std::ofstream("csgo\\materials\\regular.vmt") << R"#("VertexLitGeneric"
	{
	  "$basetexture" "vgui/white"
	  "$ignorez"      "0"
	  "$envmap"       ""
	  "$nofog"        "1"
	  "$model"        "1"
	  "$nocull"       "0"
	  "$selfillum"    "1"
	  "$halflambert"  "1"
	  "$znearer"      "0"
	  "$flat"         "1"
	})#";

	std::ofstream("csgo\\materials\\regular_xqz.vmt") << R"#("VertexLitGeneric" 
	{
		"$basetexture" "vgui/white"
		"$ignorez"      "1"
		"$envmap"       ""
		"$nofog"        "1"
		"$model"        "1"
		"$nocull"       "0"
		"$selfillum"    "1"
		"$halflambert"  "1"
		"$znearer"      "0"
		"$flat"         "1"
	})#";

	// ghost

	std::ofstream("csgo\\materials\\ghost.vmt") << R"#("VertexLitGeneric" 
    {
      "$basetexture" "vgui/white_additive"
	  "$ignorez" "0"
	  "$additive" "0"
	  "$envmap"  "models/effects/cube_white"
	  "$normalmapalphaenvmapmask" "1"
	  "$envmaptint" "[0.12 0.1 0.22]"
	  "$envmapfresnel" "1"
	  "$envmapfresnelminmaxexp" "[0 1 2]"
	  "$envmapcontrast" "1"
	  "$nofog" "1"
	  "$model" "1"
	  "$nocull" "0"
	  "$selfillum" "1"
	  "$halflambert" "1"
	  "$znearer" "0"
	  "$flat" "1"
	})#";

	std::ofstream("csgo\\materials\\ghost_xqz.vmt") << R"#("VertexLitGeneric" 
    {
      "$basetexture" "vgui/white_additive"
	  "$ignorez" "1"
	  "$additive" "0"
	  "$envmap"  "models/effects/cube_white"
	  "$normalmapalphaenvmapmask" "1"
	  "$envmaptint" "[0.12 0.1 0.22]"
	  "$envmapfresnel" "1"
	  "$envmapfresnelminmaxexp" "[0 1 2]"
	  "$envmapcontrast" "1"
	  "$nofog" "1"
	  "$model" "1"
	  "$nocull" "0"
	  "$selfillum" "1"
	  "$halflambert" "1"
	  "$znearer" "0"
	  "$flat" "1"
	})#";

	// animated

	std::ofstream("csgo\\materials\\animated.vmt") << R"#("VertexLitGeneric" 
    {
      "$envmap" "editor/cube_vertigo"
	  "$envmapcontrast" "1"
	  "$basetexture" "dev/zone_warning"
	  "proxies"
	  {
	  "texturescroll"
	  {
	  "texturescrollvar"
	  "$basetexturetransform"
	  "texturescrollrate" "0.6"
	  "texturescrollangle" "90"
	  }
	  }
	})#";


	std::ofstream("csgo\\materials\\animated_xqz.vmt") << R"#("VertexLitGeneric" 
    {
      "$envmap" "editor/cube_vertigo"
      "$ignorez" "1"
	  "$envmapcontrast" "1"
	  "$basetexture" "dev/zone_warning"
	  "proxies"
	  {
	  "texturescroll"
	  {
	  "texturescrollvar"
	  "$basetexturetransform"
	  "texturescrollrate" "0.6"
	  "texturescrollangle" "90"
	  }
	  }
	})#";

	// pearlescent 

	std::ofstream("csgo\\materials\\pearlescent.vmt") << R"#("VertexLitGeneric" 
    {
      "$basetexture" "vgui/white_additive"
	  "$ambientonly" "1"
	  "$phong"  "1"
	  "$pearlescent" "2"
	  "$basemapalphaphongmask" "1"
	})#";

	std::ofstream("csgo\\materials\\pearlescent_xqz.vmt") << R"#("VertexLitGeneric" 
    {
      "$basetexture" "vgui/white_additive"
      "$ignorez" "1"
 	  "$ambientonly" "1"
	  "$phong"  "1"
	  "$pearlescent" "2"
	  "$basemapalphaphongmask" "1"
	})#";

	// water

	std::ofstream("csgo\\materials\\water.vmt") << R"#("Refract"
	{
		"$model" "1"
			"$refractamount" "2.0"
			"$refracttint" "[0 1 1 100]"
			"$dudvmap" "dev/water_dudv"
			"$normalmap" "dev/water_normal"
			"$surfaceprop" "water"
			"$bumpframe" "0"
			"proxies"
		{
			"animatedtexture"
			{
				"animatedtexturevar" "$normalmap"
					"animatedtextureframenumvar" "$bumpframe"
					"animatedtextureframerate" "30.00"
			}
			"texturescroll"
			{
				"texturescrollvar" "$bumptransform"
					"texturescrollrate" ".05"
					"texturescrollangle" "45.00"
			}
		}
	})#";

	std::ofstream("csgo\\materials\\water_xqz.vmt") << R"#("Refract"
	{
	  "$model" "1"
      "$ignorez" "1"
	  "$refractamount" "2.0"
	  "$refracttint" "[0 1 1 100]"
	  "$dudvmap" "dev/water_dudv"
	  "$normalmap" "dev/water_normal"
	  "$surfaceprop" "water"
	  "$bumpframe" "0"
	  "proxies"
	  {
		"animatedtexture"
		{
			"animatedtexturevar" "$normalmap"
			"animatedtextureframenumvar" "$bumpframe"
			"animatedtextureframerate" "30.00"
		}
		"texturescroll"
		{
			"texturescrollvar" "$bumptransform"
				"texturescrollrate" ".05"
				"texturescrollangle" "45.00"
		}
	}
	})#";
}