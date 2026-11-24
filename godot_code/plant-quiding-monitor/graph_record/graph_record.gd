extends Control


@onready var scrol_cont = %ScrollContainer
var is_scrol_in_focus:= false

@export var max_y:int
@export var min_y:int
@export var graph_bar_scene:PackedScene
var last_change_index:int = 0

var data:Dictionary[int,float] = {}:
	set(d):
		var colum:HBoxContainer = %ColumHolder
		var new_bar:Panel = graph_bar_scene.instantiate()
		new_bar.custom_maximum_size.y = 0
		colum.add_child(new_bar)
		var maped_height = remap(d[last_change_index],min_y,max_y,0,size.y)
		var new_bar_tween:= new_bar.create_tween()
		new_bar_tween.set_trans(Tween.TRANS_CUBIC)
		new_bar_tween.set_ease(Tween.EASE_OUT)
		new_bar_tween.tween_property(new_bar,"custom_maximum_size",Vector2(new_bar.custom_maximum_size.x,maped_height),0.8)
		await new_bar.ready
		data = d



# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	if is_scrol_in_focus == false:
		scrol_cont.scroll_horizontal += 500*delta


func add_value(new_value: float):
	
	var index = data.size()
	last_change_index = index
	var new_data = data
	new_data[index] = new_value
	data = new_data







func _on_button_toggled(toggled_on: bool) -> void:
	is_scrol_in_focus = toggled_on
	if is_scrol_in_focus:
		scrol_cont.horizontal_scroll_mode = ScrollContainer.ScrollMode.SCROLL_MODE_AUTO
	else :
		scrol_cont.horizontal_scroll_mode = ScrollContainer.ScrollMode.SCROLL_MODE_SHOW_NEVER
