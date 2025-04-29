const
	MAX_FILE_NAME: integer = 101; {Max. length for file name}
	MAX_LINE: integer = 514; {Max. line length}
	MAX_NAME_LENGTH: integer = 21; {Max. length for resort name}
	DAYS_IN_WEEK: integer = 7; {Number of days in a week}
	MAX_RESORTS: integer = 20; {Max. number of ski resorts}
	FAHRENHEIT_FACTOR: real = 1.8; {Conversion factor from Celsius to Fahrenheit}
	FAHRENHEIT_OFFSET: real = 32.0; {Offset for Fahrenheit conversion}
	SNOW_TEMP_THRESHOLD: real = 0.0; {Temperature threshold for snow}
	SNOW_RAIN_THRESHOLD: real = 10.0; {Rainfall threshold for snow}
end const

type
	{User defined types}
	tTemperature = {CELSIUS = 1, FAHRENHEIT = 2} {Temperature scale type}
	tWeatherData = record
		temperature: real; {Temperature in Celsius}
		rainAccumulation: real; {Rain accumulation in millimeters}
	end record
	tSkiResort = record
		resortName: string; {Resort name}
		weekData: vector[DAYS_IN_WEEK] of tWeatherData; {Weather data for each day of the week}
	end record
end type
{Exercise 1} 

{Function that converts celsius to farenheit}
function celsiusToFahrenheit (temperatureCelsius: integer): real
	{F = C * 9/5 + 32}
	var
		temperatureFahrenheit: real;
	end var
	temperatureFahreneit = 0.0;
	temperatureFahrenheit = temperatureCelsius * FAHRENHEIT_FACTOR + FAHRENHEIT_OFFSET;
	return temperatureFahrenheit;
end function

{Exercise 2}
function avgTemperature (sumTemperatures: real, days: integer) real
	var
		float avgTemp = 0.00f;
	avgTemp = sumTemperatures/integerToReal(days);
	return avgTemp;
end function
{Exercise 3} 
function isSnowyWeek (weekData[]: tWeatherData, days: integer): boolean
	var
		i: integer;
	end var
	for  i := 0 to days do
		if weekData[i].temperature <= SNOW_TEMP_THRESHOLD and weekData[i].rainAccumulation >= SNOW_RAIN_THRESHOLD then
			return true; 
		else
			return false; 
		end if
	end for
end function	

algorithm SkiResortWeather
	var
		resorts: vector[MAX_RESORTS] of tSkiResort;
		resortCount: integer;
		i: integer;
		filename: string;
		avgTemp: real;
		itWillSnow: boolean;
		temperatureScale: tTemperature;
		isRead: boolean;
		sumTemperatures: real;
	end var
	{Load data from file}
	writeString("LOAD DATA FROM FILE. ENTER FILE NAME >>");
	filename := readString();
	loadSkiResortsDataFromFile(filename, resorts, resortCount, isRead);
	if isRead then {Data successfully loaded}
		{Exercise 4}
		{Data input}
		{Input the temperature scale}
		do
			writeString("SELECT TEMPERATURE SCALE (1-CELSIUS, 2-FAHRENHEIT) >>");
			temperatureScale := readInteger();
			if temperatureScale < CELSIUS or temperatureScale > FAHRENHEIT then
				writeString("INVALID DATA, TRY AGAIN! \n");
			end if
		while temperatureScale < CELSIUS or temperatureScale > FAHRENHEIT;
		if temperatureScale == 2/FAHRENHEIT then
			for i := 1 in DAYS_IN_WEEK do
				celsiusToFahrenheit(resorts.weekData.temperature)
			end for
		end if
		
		{Exercise 5}
		{Data Output}
		writeString("NAME AVG_TEMP IT_WILL_SNOW (1-TRUE, 0-FALSE)");
		writeString("--------------------------------------------"); 
		for i := 1 to resortCount do
			itWillSnow = isSnowyWeek(resorts[i].weekData, DAYS_IN_WEEK):
				for d := 1 to DAYS_IN_WEEK do
					if temperatureScale == FAHRENHEIT then
						resorts[i].weekData[d].temperature = celsiusToFahrenheit(resorts[i].weekData[d].temperature
					end if
					sumTemperatures = sumTemperatures + resorts[i].weekData[d].temperature
				end for
				avgTemp = avgTemperature(sumTemperatures, DAYS_IN_WEEK)
				writeString(resorts[i].resortName)
				writeReal(avgTemp)
				writeBool(itWillSnow)
		end for
	else 
		writeString("NO RESORTS RECOVERED")
	end if
end algorithm