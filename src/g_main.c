/*
 * =======================================================================
 *
 * Jump in into the game.so and support functions.
 *
 * =======================================================================
 */

#include "header/local.h"

game_locals_t game;
level_locals_t level;
game_import_t gi;
game_export_t globals;
spawn_temp_t st;

int sm_meat_index;
int snd_fry;
int meansOfDeath;

edict_t *g_edicts;

cvar_t *deathmatch;
cvar_t *coop;
cvar_t *coop_baseq2;	/* treat spawnflags according to baseq2 rules */
cvar_t *coop_elevator_delay;
cvar_t *coop_pickup_weapons;
cvar_t *dmflags;
cvar_t *skill;
cvar_t *fraglimit;
cvar_t *timelimit;
cvar_t *password;
cvar_t *spectator_password;
cvar_t *needpass;
cvar_t *maxclients;
cvar_t *maxspectators;
cvar_t *maxentities;
cvar_t *g_select_empty;
cvar_t *dedicated;
cvar_t *g_footsteps;
cvar_t *g_fix_triggered;

cvar_t *filterban;

cvar_t *sv_maxvelocity;
cvar_t *sv_gravity;

cvar_t *sv_rollspeed;
cvar_t *sv_rollangle;
cvar_t *gun_x;
cvar_t *gun_y;
cvar_t *gun_z;

cvar_t *run_pitch;
cvar_t *run_roll;
cvar_t *bob_up;
cvar_t *bob_pitch;
cvar_t *bob_roll;

cvar_t *sv_cheats;

cvar_t *flood_msgs;
cvar_t *flood_persecond;
cvar_t *flood_waitdelay;

cvar_t *sv_maplist;
cvar_t *sv_stopspeed;

cvar_t *g_showlogic;
cvar_t *gamerules;
cvar_t *huntercam;
cvar_t *strong_mines;
cvar_t *randomrespawn;

cvar_t *g_disruptor;

cvar_t *aimfix;
cvar_t *g_machinegun_norecoil;

cvar_t *sv_custom_settings;

cvar_t *cs_player_health_start;
cvar_t *cs_player_health_max;

cvar_t *cs_player_ammo_shells;
cvar_t *cs_player_ammo_bullets;
cvar_t *cs_player_ammo_grenades;
cvar_t *cs_player_ammo_rockets;
cvar_t *cs_player_ammo_slugs;
cvar_t *cs_player_ammo_cells;

cvar_t *cs_player_ammo_prox;
cvar_t *cs_player_ammo_tesla;
cvar_t *cs_player_ammo_flechettes;
cvar_t *cs_player_ammo_rounds;

cvar_t *cs_bandolier_ammo_shells;
cvar_t *cs_bandolier_ammo_bullets;
cvar_t *cs_bandolier_ammo_grenades;
cvar_t *cs_bandolier_ammo_rockets;
cvar_t *cs_bandolier_ammo_slugs;
cvar_t *cs_bandolier_ammo_cells;

cvar_t *cs_bandolier_ammo_flechettes;
cvar_t *cs_bandolier_ammo_rounds;

cvar_t *cs_ammopack_ammo_shells;
cvar_t *cs_ammopack_ammo_bullets;
cvar_t *cs_ammopack_ammo_grenades;
cvar_t *cs_ammopack_ammo_rockets;
cvar_t *cs_ammopack_ammo_slugs;
cvar_t *cs_ammopack_ammo_cells;

cvar_t *cs_ammopack_ammo_flechettes;
cvar_t *cs_ammopack_ammo_rounds;
cvar_t *cs_ammopack_ammo_prox;
cvar_t *cs_ammopack_ammo_tesla;

cvar_t *cs_silencer_shots_quantity;
cvar_t *cs_quad_duration;
cvar_t *cs_rebreather_duration;
cvar_t *cs_environmentsuit_duration;
cvar_t *cs_invulnerability_duration;
cvar_t *cs_powerup_quantity_easy;
cvar_t *cs_powerup_quantity_medium;
cvar_t *cs_powerup_quantity_hard;
cvar_t *cs_powerup_quantity_hardplus;

cvar_t *cs_IR_duration;
cvar_t *cs_double_duration;

cvar_t *cs_health_small_val;
cvar_t *cs_health_val;
cvar_t *cs_health_large_val;
cvar_t *cs_health_mega_val;
cvar_t *cs_health_mega_decay;
cvar_t *cs_adrenaline_val;
cvar_t *cs_adrenaline_heal;
cvar_t *cs_ancienthead_val;
cvar_t *cs_ancienthead_heal;
cvar_t *cs_player_health_cap;
cvar_t *cs_player_health_force_max;

cvar_t *cs_armor_shard_val;
cvar_t *cs_armor_jacket_val;
cvar_t *cs_armor_combat_val;
cvar_t *cs_armor_body_val;
cvar_t *cs_armor_jacket_max;
cvar_t *cs_armor_combat_max;
cvar_t *cs_armor_body_max;
cvar_t *cs_armor_jacket_absp;
cvar_t *cs_armor_combat_absp;
cvar_t *cs_armor_body_absp;
cvar_t *cs_armor_jacket_abse;
cvar_t *cs_armor_combat_abse;
cvar_t *cs_armor_body_abse;
cvar_t *cs_player_armor_cap;
cvar_t *cs_player_armor_force_max;

cvar_t *cs_etf_deplete_cell_mul;

cvar_t *cs_power_armor_screen_dmgxcell;
cvar_t *cs_power_armor_screen_dmg_mul;
cvar_t *cs_power_armor_screen_dmg_div;
cvar_t *cs_power_armor_shield_dmgxcell;
cvar_t *cs_power_armor_shield_dmg_mul;
cvar_t *cs_power_armor_shield_dmg_div;

cvar_t *cs_damage_modifier_hardplus;
cvar_t *cs_damage_modifier_hard;
cvar_t *cs_damage_modifier_medium;
cvar_t *cs_damage_modifier_easy;
cvar_t *cs_damage_sneak_attack;

cvar_t *cs_weapon_blaster_damage_sp;
cvar_t *cs_weapon_blaster_damage_mp;
cvar_t *cs_weapon_blaster_speed;

cvar_t *cs_weapon_shotgun_bullets;
cvar_t *cs_weapon_shotgun_damage;
cvar_t *cs_weapon_shotgun_kick;
cvar_t *cs_weapon_shotgun_hspread;
cvar_t *cs_weapon_shotgun_vspread;

cvar_t *cs_weapon_sshotgun_bullets;
cvar_t *cs_weapon_sshotgun_damage;
cvar_t *cs_weapon_sshotgun_kick;
cvar_t *cs_weapon_sshotgun_hspread;
cvar_t *cs_weapon_sshotgun_vspread;
cvar_t *cs_weapon_sshotgun_yaw;

cvar_t *cs_weapon_machinegun_damage;
cvar_t *cs_weapon_machinegun_kick;
cvar_t *cs_weapon_machinegun_hspread;
cvar_t *cs_weapon_machinegun_vspread;
cvar_t *cs_weapon_machinegun_recoil;

cvar_t *cs_weapon_chaingun_damage_sp;
cvar_t *cs_weapon_chaingun_damage_mp;
cvar_t *cs_weapon_chaingun_kick;
cvar_t *cs_weapon_chaingun_hspread;
cvar_t *cs_weapon_chaingun_vspread;

cvar_t *cs_weapon_grenade_hand_damage_direct;
cvar_t *cs_weapon_grenade_hand_damage_radius;
cvar_t *cs_weapon_grenade_hand_speed_min;
cvar_t *cs_weapon_grenade_hand_speed_max;

cvar_t *cs_weapon_grenade_launcher_damage_direct;
cvar_t *cs_weapon_grenade_launcher_damage_radius;
cvar_t *cs_weapon_grenade_launcher_speed;

cvar_t *cs_weapon_grenade_launcher_damage_direct_p;

cvar_t *cs_weapon_rocket_launcher_damage_direct;
cvar_t *cs_weapon_rocket_launcher_damage_radius;
cvar_t *cs_weapon_rocket_launcher_radius;
cvar_t *cs_weapon_rocket_launcher_speed;

cvar_t *cs_weapon_hblaster_damage_sp;
cvar_t *cs_weapon_hblaster_damage_mp;
cvar_t *cs_weapon_hblaster_speed;

cvar_t *cs_weapon_railgun_damage_sp;
cvar_t *cs_weapon_railgun_damage_mp;
cvar_t *cs_weapon_railgun_kick_sp;
cvar_t *cs_weapon_railgun_kick_mp;

cvar_t *cs_weapon_bfg_damage_effect_sp;
cvar_t *cs_weapon_bfg_damage_effect_mp;
cvar_t *cs_weapon_bfg_radius;
cvar_t *cs_weapon_bfg_speed;

cvar_t *cs_weapon_chainfist_damage_sp;
cvar_t *cs_weapon_chainfist_damage_mp;
cvar_t *cs_weapon_chainfist_reach;

cvar_t *cs_weapon_disintegrator_damage_sp;
cvar_t *cs_weapon_disintegrator_damage_mp;

cvar_t *cs_weapon_etf_rifle_damage;
cvar_t *cs_weapon_etf_rifle_kick;
cvar_t *cs_weapon_etf_rifle_speed;

cvar_t *cs_weapon_heatbeam_damage_sp;
cvar_t *cs_weapon_heatbeam_damage_mp;
cvar_t *cs_weapon_heatbeam_kick_sp;
cvar_t *cs_weapon_heatbeam_kick_mp;

cvar_t *cs_weapon_bfg_damage_direct;
cvar_t *cs_weapon_bfg_damage_radius;
cvar_t *cs_weapon_bfg_damage_laser_sp;
cvar_t *cs_weapon_bfg_damage_laser_mp;

cvar_t *cs_prox_time_to_live;
cvar_t *cs_prox_time_delay;
cvar_t *cs_prox_bound_size;
cvar_t *cs_prox_damage_radius;
cvar_t *cs_prox_health;
cvar_t *cs_prox_damage;

cvar_t *cs_tesla_time_to_live;
cvar_t *cs_tesla_damage_radius;
cvar_t *cs_tesla_damage;
cvar_t *cs_tesla_knockback;
cvar_t *cs_tesla_activate_time;
cvar_t *cs_tesla_explosion_damage_mult;
cvar_t *cs_tesla_explosion_radius;
cvar_t *cs_tesla_health_sp;
cvar_t *cs_tesla_health_mp;

cvar_t *cs_nuke_delay;
cvar_t *cs_nuke_time_to_live;
cvar_t *cs_nuke_radius;
cvar_t *cs_nuke_damage;
cvar_t *cs_nuke_quake_time;
cvar_t *cs_nuke_quake_strength;

cvar_t *cs_turret_blaster_damage;
cvar_t *cs_turret_rocket_damage_direct;
cvar_t *cs_turret_rocket_damage_radius;
cvar_t *cs_turret_rocket_radius;
cvar_t *cs_turret_rocket_speed;

cvar_t *cs_monster_turret_blaster_damage;
cvar_t *cs_monster_turret_machinegun_damage;
cvar_t *cs_monster_turret_rocket_damage;
cvar_t *cs_monster_turret_health;

void SpawnEntities(char *mapname, char *entities, char *spawnpoint);
void ClientThink(edict_t *ent, usercmd_t *cmd);
qboolean ClientConnect(edict_t *ent, char *userinfo);
void ClientUserinfoChanged(edict_t *ent, char *userinfo);
void ClientDisconnect(edict_t *ent);
void ClientBegin(edict_t *ent);
void ClientCommand(edict_t *ent);
void RunEntity(edict_t *ent);
void WriteGame(char *filename, qboolean autosave);
void ReadGame(char *filename);
void WriteLevel(char *filename);
void ReadLevel(char *filename);
void InitGame(void);
void G_RunFrame(void);

/* =================================================================== */

void
ShutdownGame(void)
{
	gi.dprintf("==== ShutdownGame ====\n");

	gi.FreeTags(TAG_LEVEL);
	gi.FreeTags(TAG_GAME);
}

/*
 * Returns a pointer to the structure with
 * all entry points and global variables
 */
game_export_t *
GetGameAPI(game_import_t *import)
{
	gi = *import;

	globals.apiversion = GAME_API_VERSION;
	globals.Init = InitGame;
	globals.Shutdown = ShutdownGame;
	globals.SpawnEntities = SpawnEntities;

	globals.WriteGame = WriteGame;
	globals.ReadGame = ReadGame;
	globals.WriteLevel = WriteLevel;
	globals.ReadLevel = ReadLevel;

	globals.ClientThink = ClientThink;
	globals.ClientConnect = ClientConnect;
	globals.ClientUserinfoChanged = ClientUserinfoChanged;
	globals.ClientDisconnect = ClientDisconnect;
	globals.ClientBegin = ClientBegin;
	globals.ClientCommand = ClientCommand;

	globals.RunFrame = G_RunFrame;

	globals.ServerCommand = ServerCommand;

	globals.edict_size = sizeof(edict_t);

	/* Seed the PRNG */
	randk_seed();

	return &globals;
}

/*
 * this is only here so the functions in
 * q_shared.c and q_shwin.c can link
 */
void
Sys_Error(char *error, ...)
{
	va_list argptr;
	char text[1024];

	va_start(argptr, error);
	vsprintf(text, error, argptr);
	va_end(argptr);

	gi.error("%s", text);
}

void
Com_Printf(char *msg, ...)
{
	va_list argptr;
	char text[1024];

	va_start(argptr, msg);
	vsprintf(text, msg, argptr);
	va_end(argptr);

	gi.dprintf("%s", text);
}

/* ====================================================================== */

void
ClientEndServerFrames(void)
{
	int i;
	edict_t *ent;

	/* calc the player views now that all
	   pushing and damage has been added */
	for (i = 0; i < maxclients->value; i++)
	{
		ent = g_edicts + 1 + i;

		if (!ent->inuse || !ent->client)
		{
			continue;
		}

		ClientEndServerFrame(ent);
	}
}

/*
 * Returns the created target changelevel
 */
edict_t *
CreateTargetChangeLevel(char *map)
{
	edict_t *ent;

	if (!map)
	{
		return NULL;
	}

	ent = G_Spawn();
	ent->classname = "target_changelevel";
	Com_sprintf(level.nextmap, sizeof(level.nextmap), "%s", map);
	ent->map = level.nextmap;
	return ent;
}

/*
 * The timelimit or fraglimit has been exceeded
 */
void
EndDMLevel(void)
{
	edict_t *ent;
	char *s, *t, *f;
	static const char *seps = " ,\n\r";

	/* stay on same level flag */
	if ((int)dmflags->value & DF_SAME_LEVEL)
	{
		BeginIntermission(CreateTargetChangeLevel(level.mapname));
		return;
	}

	/* see if it's in the map list */
	if (*sv_maplist->string)
	{
		s = strdup(sv_maplist->string);
		f = NULL;
		t = strtok(s, seps);

		while (t != NULL)
		{
			if (Q_stricmp(t, level.mapname) == 0)
			{
				/* it's in the list, go to the next one */
				t = strtok(NULL, seps);

				if (t == NULL) /* end of list, go to first one */
				{
					if (f == NULL) /* there isn't a first one, same level */
					{
						BeginIntermission(CreateTargetChangeLevel(level.mapname));
					}
					else
					{
						BeginIntermission(CreateTargetChangeLevel(f));
					}
				}
				else
				{
					BeginIntermission(CreateTargetChangeLevel(t));
				}

				free(s);
				return;
			}

			if (!f)
			{
				f = t;
			}

			t = strtok(NULL, seps);
		}

		free(s);
	}

	if (level.nextmap[0]) /* go to a specific map */
	{
		BeginIntermission(CreateTargetChangeLevel(level.nextmap));
	}
	else /* search for a changelevel */
	{
		ent = G_Find(NULL, FOFS(classname), "target_changelevel");

		if (!ent)
		{
			/* the map designer didn't include a changelevel,
			   so create a fake ent that goes back to the same
			   level */
			BeginIntermission(CreateTargetChangeLevel(level.mapname));
			return;
		}

		BeginIntermission(ent);
	}
}

void
CheckNeedPass(void)
{
	int need;

	/* if password or spectator_password has
	   changed, update needpass as needed */
	if (password->modified || spectator_password->modified)
	{
		password->modified = spectator_password->modified = false;

		need = 0;

		if (*password->string && Q_stricmp(password->string, "none"))
		{
			need |= 1;
		}

		if (*spectator_password->string &&
			Q_stricmp(spectator_password->string, "none"))
		{
			need |= 2;
		}

		gi.cvar_set("needpass", va("%d", need));
	}
}

void
CheckDMRules(void)
{
	int i;
	gclient_t *cl;

	if (level.intermissiontime)
	{
		return;
	}

	if (!deathmatch->value)
	{
		return;
	}

	if (gamerules && gamerules->value && DMGame.CheckDMRules)
	{
		if (DMGame.CheckDMRules())
		{
			return;
		}
	}

	if (timelimit->value)
	{
		if (level.time >= timelimit->value * 60)
		{
			gi.bprintf(PRINT_HIGH, "Timelimit hit.\n");
			EndDMLevel();
			return;
		}
	}

	if (fraglimit->value)
	{
		for (i = 0; i < maxclients->value; i++)
		{
			cl = game.clients + i;

			if (!g_edicts[i + 1].inuse)
			{
				continue;
			}

			if (cl->resp.score >= fraglimit->value)
			{
				gi.bprintf(PRINT_HIGH, "Fraglimit hit.\n");
				EndDMLevel();
				return;
			}
		}
	}
}

void
ExitLevel(void)
{
	int i;
	edict_t *ent;
	char command[256];

	Com_sprintf(command, sizeof(command), "gamemap \"%s\"\n", level.changemap);
	gi.AddCommandString(command);
	level.changemap = NULL;
	level.exitintermission = 0;
	level.intermissiontime = 0;
	ClientEndServerFrames();

	/* clear some things before going to next level */
	for (i = 0; i < maxclients->value; i++)
	{
		ent = g_edicts + 1 + i;

		if (!ent->inuse)
		{
			continue;
		}

		if (ent->health > ent->max_health)
		{
			ent->health = ent->max_health;
		}
	}

	debristhisframe = 0;
	gibsthisframe = 0;
}

/*
 * Advances the world by 0.1 seconds
 */
void
G_RunFrame(void)
{
	int i;
	edict_t *ent;

	level.framenum++;
	level.time = level.framenum * FRAMETIME;

	debristhisframe = 0;
	gibsthisframe = 0;

	/* choose a client for monsters to target this frame */
	AI_SetSightClient();

	/* exit intermissions */
	if (level.exitintermission)
	{
		ExitLevel();
		return;
	}

	/* treat each object in turn  even the
	   world gets a chance to think */
	ent = &g_edicts[0];

	for (i = 0; i < globals.num_edicts; i++, ent++)
	{
		if (!ent->inuse)
		{
			continue;
		}

		level.current_entity = ent;

		VectorCopy(ent->s.origin, ent->s.old_origin);

		/* if the ground entity moved, make sure we are still on it */
		if ((ent->groundentity) &&
			(ent->groundentity->linkcount != ent->groundentity_linkcount))
		{
			ent->groundentity = NULL;

			if (!(ent->flags & (FL_SWIM | FL_FLY)) &&
				(ent->svflags & SVF_MONSTER))
			{
				M_CheckGround(ent);
			}
		}

		if ((i > 0) && (i <= maxclients->value))
		{
			ClientBeginServerFrame(ent);
			continue;
		}

		G_RunEntity(ent);
	}

	/* see if it is time to end a deathmatch */
	CheckDMRules();

	/* see if needpass needs updated */
	CheckNeedPass();

	/* build the playerstate_t structures for all players */
	ClientEndServerFrames();
}
