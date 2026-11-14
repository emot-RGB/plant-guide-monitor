extends Control


# Called when the node enters the scene tree for the first time.

var current_record:Record = Record.new():
	set(a):
		%TemperatureLabel.text =  str(a.temperature.value) + a.temperature.unit
		%HumidityLabel.text = str(a.humidity.value) + a.humidity.unit
		%SoilHumidityLabel.text = str(a.soil_humidity.value) + a.humidity.unit
		var max = int(%max.text)
		if a.soil_humidity.value > max:
			%max.text = str(a.soil_humidity.value)
		var min = int(%min.text)
		if a.soil_humidity.value < min:
			%min.text = str(a.soil_humidity.value)
		current_record = a
	get:
		return current_record


@onready var http_request:HTTPRequest = %HTTPRequest
func _ready() -> void:
	http_request.connect("request_completed",request_completed)
	get_value()
	pass # Replace with function body.



var timer:float 

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	timer += delta
	if timer > 0.1:
		if http_request.get_http_client_status() == HTTPClient.Status.STATUS_DISCONNECTED:
			get_value()
		timer=0
	pass


func get_value():
	http_request.request(%LineEdit.text)


func request_completed(result: int, response_code: int, headers: PackedStringArray, body: PackedByteArray):
	var string:PackedStringArray = body.get_string_from_utf8().split("\n",false)
	
	if current_record:
		current_record = current_record.from_json_str(body.get_string_from_utf8())
	else:
		current_record = Record.new().from_json_str(body.get_string_from_utf8())
	
