class_name  Sensor
extends Node



@export var unit:String :
	set(a):
		unit = a
		changed.emit(self)

@export var value:float:
	set(a):
		value = a
		changed.emit(self)

signal changed(sensor:Sensor)
