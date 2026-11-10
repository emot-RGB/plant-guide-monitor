extends Control


# Called when the node enters the scene tree for the first time.
@onready var http_request:HTTPRequest = %HTTPRequest
func _ready() -> void:
	get_value()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass



func get_value():
	http_request.connect("request_completed",request_completed)
	http_request.request("https://books.toscrape.com/catalogue/a-light-in-the-attic_1000/index.html")
	
	



func request_completed(result: int, response_code: int, headers: PackedStringArray, body: PackedByteArray):
	var string:PackedStringArray = body.get_string_from_utf8().split("\n",false)
	
	for i in string:
		print(i)
		#await get_tree().create_timer(0.0).timeout
	
	Record.new().from_json_str()
	
