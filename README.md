Note: All commands should be entered in lowercase, except for names would should be capitalized as proper nouns.
Commands:

wait
	wait [amount]
	amount is taken as an integer
	Runs the simulation the given amount of times

mine
	mine [amount] [ore]
	amount is taken as an integer.
	ore is taken as a string.
	Sends a dwarf to mine the specified amount of ore.  Possible ore types are coal, iron, and gold.

chop
	chop [amount] [wood]
	amount is taken as an integer.
	ore is taken as a string.
	Sends a dwarf to chop the specified amount of wood.  Possible wood types are redwood, birch, and oak.

fish
	fish [amount] [fishType]
	amount is taken as an integer.
	fishType is taken as a string.
	Sends a dwarf to fish for the specified amount of fish.  Possible fish types are tuna, salmon, and swordfish.

drink
	drink
	Sends a dwarf to begin drinking at the Pub.
	
focus
	focus [dwarf name]
	dwarf name is taken as a string with the first letter capitalized.
	Dwarves: Bob, Jim, Joe, Phil, and Frank.
	focus allows you to control what one specific dwarf does.
	
	While focused, you can execute these commands:
	eat
		eat [amount] [food]
		amount is taken as an integer.
		type is taken as a string.
		Directs the dwarf to eat the specified food.  Possible food types are fish.

	craft
		
	inventory
		inventory
		Prints the focused actor's inventory
		
	lose focus
		lose focus
		Returns focus back to the village