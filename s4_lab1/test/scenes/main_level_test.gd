class_name MainLevelTest
extends GdUnitTestSuite

# TestSuite generated from
const __source = 'res://scenes/main_level.gd'

var spy_scene
#var _player :player

func before():
  var scene_instance = load("res://scenes/main_level.tscn").instance()
  spy_scene = spy(scene_instance)
  
  # set time factor to 10 to simulate the scene very fast
  #runner.set_time_factor(1)
  
  # enable this line to show the running scene during test execution
  #_runner.maximize_view()
  
  #_player = _scene.find_node("player")

func before_test():
  reset(spy_scene)

func test_score_update():
	var scene_runner := scene_runner(spy_scene)
	var pos_to_move = -80
	
	assert_int(spy_scene.score).is_equal(0)
	spy_scene.player.position.y = pos_to_move
	yield(await_idle_frame(), "completed") 
	assert_int(int(spy_scene.score)).is_equal(spy_scene.intital_camera_position_y - spy_scene.camera.position.y);

func test_player_death():
	var scene_runner := scene_runner(spy_scene)
	var enemy = load("res://scenes/enemy.tscn").instance()
	spy_scene.platform_generator.call_deferred("add_child", enemy)
	enemy.speed = 0
	enemy.position = Vector2(spy_scene.player.position.x, spy_scene.player.position.y  - 25)
	spy_scene.player.velocity.y = spy_scene.player.jump_velocity
	
	#yield(scene_runner.await_signal_on(spy_scene.platform_eraser, "_on_platform_eraser_body_entered"), "completed")
	#yield(scene_runner.simulate_frames(60), "completed")
	yield(scene_runner.simulate_frames(10), "completed")
	assert_bool(spy_scene.player.game_over).is_equal(true)
	enemy.free()
