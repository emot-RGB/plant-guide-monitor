class_name Record
extends Node
var date_time:String

var humidity:Sensor = Sensor.new()
var soil_humidity:Sensor = Sensor.new()
var temperature:Sensor = Sensor.new()

#func new(humidity:Sensor,soil_humidity:Sensor,temperature:Sensor,date_time:Sensor) -> Record:
	#return self

func from_json_str(json_string:String)-> Record:
	date_time = Time.get_datetime_string_from_system()
	#var json_string:String = """
	#{
  #"record": {
	#"sensors": {
	  #"temperature": {
		#"value": 0,
		#"unit": "ºC"
	  #},
	  #"humidity": {
		#"value": 0,
		#"unit": "%"
	  #},
	  #"soil-humidity": {
		#"value": 0,
		#"unit": "%"
	  #}
	#}
  #}
#}
#"""
	if json_string.is_empty() == false and json_string.split("\n").size() > 2:
		print(json_string)
		var json:Dictionary = JSON.parse_string(json_string)
		if json["record"]["sensors"]["temperature"]["unit"] != "":
			temperature.value = json["record"]["sensors"]["temperature"]["value"]
			temperature.unit = json["record"]["sensors"]["temperature"]["unit"]
			
			humidity.value = json["record"]["sensors"]["humidity"]["value"]
			humidity.unit = json["record"]["sensors"]["humidity"]["unit"]
			
			soil_humidity.value = json["record"]["sensors"]["soil-humidity"]["value"]
			soil_humidity.unit = json["record"]["sensors"]["soil-humidity"]["unit"]
	
	return self
