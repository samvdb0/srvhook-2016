# Fiesta.ServerHooks.2016
A set of dynamic link libraries aiming to extend the functionality of Fiesta Online's 2016 (TeamNG) server files.

# Disclaimer
Note that this project isn't fool-proof, there are many unfixed issues with the features this provides that have to be fixed before using this on a public server and may or may not work properly depending on your server setup.

# Features
- **Security fixes:**
  - Gamigo GR authentication is no longer required.
  - Automatic shutdown after 4 days has been removed.

- **Bug fixes:**
  - ItemActions/Set effects no longer randomly break after hitting a softcap.
  - Party loot allocation with Cen has been fixed.

- **Exploit fixes:**
  - Several skill usage exploits have been fixed.
  - Several crash exploits have been fixed.
  - Several lag exploits have been fixed.
  - Map-wide gathering has been fixed.
  - Instant gathering has been fixed.
  - Lucky House gembug has been fixed.
  - The ability to remove unremovable buffs has been fixed.
  - Town Gate linking from anywhere on a map has been fixed.
  - Item Combine dupe has been fixed.
  - Guild storage withdrawal as academy member has been fixed.
  
- **New QoL/features:**
  - Automatically learn skills upon level up.
  - Make mobs give a percentage of the current level's experience.
  - Drop system rework:
    - Support for Cen columns in ItemDropTable.txt has been added.
  - Ability to toggle double gathering rewards.
  - Ability to disable raids per map.
  - Solo/Guild instances have been implemented.
  - Instance dungeon ranking now gets saved to database as intended (broken if user has over 32 instances).
  - Instance dungeon limit has been removed.
  - NPC merchant limit has been removed.
  - KQ/Instance MobRegen cap has been removed.
  - Ability to set a limit of maximum Hammer Of Bijou uses per item.
  - Ability to toggle skin deletion upon hitting 0 durability.
  - Ability to announce/log the pickup of items.
  - Ability to set default walk & run speed.
  - Ability to set the backup map on link failure.
  - Object abstate cap has been increased from 28 to 128.
  - A serverside system to "fix" animation modifying has been added.
  - A scripting API for WM/Zone has been added, allowing the user to create custom commands using lua.
  - A bunch of new lua functions have been added.

# Installation
- Drop all required files in your server folder.
  - Overwrite your services with the ones under `_Files`, matching your crypto.
  - Put all `9Data` files in your `9Data` folder. 
  - Restore all SQL files under `_Files`
- Build the hook DLL's.
- Put your freshly built DLL's into the root of your server directory.
- Configure the hook to your needs using `Config.ini`
- Depending wether you compiled `CONSOLE` or not, either run the service normally or start it by double clicking the service binary.
