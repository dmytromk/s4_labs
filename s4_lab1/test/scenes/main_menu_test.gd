class_name MainMenuTest
extends GdUnitTestSuite

# TestSuite generated from
const __source = 'res://scenes/main_menu.gd'

var spy_scene

func before():
	var scene_instance = load("res://scenes/main_menu.tscn").instance()
	spy_scene = spy(scene_instance)
	
func before_test():
	reset(spy_scene)

func test_main_menu_highscore():
	scene_runner(spy_scene)
	var savegame = File.new()
	var save_path = "user://savegame.save"
	savegame.open(save_path, File.READ) 
	var save_data = savegame.get_var() 
	savegame.close() 
	var highscore = save_data["highscore"]
	
	#verify(spy_scene, 0)._on_CheckBox_toggled(any_bool())
