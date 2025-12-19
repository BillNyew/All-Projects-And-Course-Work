### Tests
NO, CANT RUN ANY TESTS
The following are test JSON strings to be pasted into Serial

{"mtype":"door_sensor1.start_alarm","from":"brain","to":"door_sensor1"}
{"mtype":"door_sensor1.stop","from":"brain","to":"door_sensor1"}
{"mtype":"door_sensor1.start_continuous","from":"brain","to":"door_sensor1"}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"polling_rate_hz","value":5}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"door_open_threshold","value":3}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"broadcast_rate_hz","value":2}
{"mtype":"door_sensor1.start_alarm","from":"brain","to":"other_sensor"}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"polling_rate_hz","value":0}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"door_open_threshold","value":20}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"broadcast_rate_hz","value":10}
{"mtype":"door_sensor1.start_alarm","from":"brain","to":"door_sensor1","extra":"unexpected"}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"unknown_param","value":123}
{"mtype":"door_sensor1.start_alarm","from":"brain","to":"door_sensor1"}
{"mtype":"door_sensor1.stop","from":"brain","to":"door_sensor1"}
{"mtype":"door_sensor1.start_continuous","from":"brain","to":"door_sensor1"}