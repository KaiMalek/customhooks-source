static const char* loggerforlogs[] = { "Damage Dealt", "Purchases" };

const char* chams_type[] =
{
    "Regular ",
    "Flat ",
    "Adv. Regular ",
    "Shiny ",
    "Pearlescent ",
    "Animated ",
    "Water "
};

std::string data_center_list[] = { "", "syd", "vie", "gru", "scl", "dxb", "par", "fra", "hkg",
"maa", "bom", "tyo", "lux", "ams", "limc", "man", "waw", "sgp", "jnb",
"mad", "sto", "lhr", "atl", "eat", "ord", "lax", "mwh", "okc", "sea", "iad" };

const char* region[] = { "Default", "Australia", "Austria", "Brazil", "Chile", "Dubai", "France", "Germany", "Hong Kong", "India (Chennai)", "India (Mumbai)", "Japan", "Luxembourg",
   "Netherlands", "Peru", "Philipines", "Poland", "Singapore", "South Africa", "Spain", "Sweden", "UK", "USA (Atlanta)", "USA (Seattle)", "USA (Chicago)", "USA (Los Angeles)", "USA (Moses Lake)",
   "USA (Oklahoma)", "USA (Seattle)", "USA (Washington DC)" };

static std::string* force_relay_cluster_value = *(std::string**)(utilities::pattern_scan("steamnetworkingsockets.dll", "B8 ? ? ? ? B9 ? ? ? ? 0F 43") + 1);