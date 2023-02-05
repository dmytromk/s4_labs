extends StaticBody2D

export var jump_multiplication_effect = 1.25

var direction = Vector2.RIGHT
var speed = 80 * Global.insane_mode
var size_x = 15

var velocity = Vector2.ZERO
var right_border = 0

func _ready():
	right_border = get_viewport_rect().size

func _physics_process(delta):
	velocity = direction * speed
	position += velocity * delta
	if position.x >= right_border.x-size_x:
		direction *= -1
	elif position.x <= size_x:
		direction *= -1

func _on_Area2D_body_entered(body):
	if body.is_in_group("player"):
		body.die()
