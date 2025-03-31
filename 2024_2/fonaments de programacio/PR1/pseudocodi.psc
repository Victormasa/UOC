const 
	DAYS_OF_THE_WEEK: integer = 7; {Number of days in a week}
	HEAVY_RAIN_THRESHOLD: real = 50.0; {Heavy rain threshold in millimeters}
	MAX_TEMP: integer = 10; {Temperature considered a disruptive change}
end const

type
	tDays = {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY}
end type

algorithm WeatherForecast

	{Variable definitions}
	var
		avgTemperatures: vector[DAYS_OF_THE_WEEK] of integer; {Estimated daily average temperature, CELSIUS}
		avgRainFall: vector[DAYS_OF_THE_WEEK] of i; {Estimated daily average rainfall, MILLIMETERS}
		heavyRainfallDays: vector[DAYS_OF_THE_WEEK] of integer; {Estimated days with heavy rainfall}
		abruptChangeTemperatureDays: vector[DAYS_OF_THE_WEEK] of integer; {Days with abrupt temperature changes}
		i: integer; {Iteration variable}
		abruptChangeCount: integer; {Counter for abrupt temperature change days}
		sumTemperature: real; {Sum of temperatures}
		sumRain: real; {Sum of rainfall in millimeters}
		fileToRead: file; {Data file}
		filename: string; {Name of data file}
		averageTemperature: real; {Average temperature of the week}
		averageRainfall: real; {Average rainfall of the week}
		heavyRainfallCount: integer; {Count for heavy rainfall days}
	end var

	{Variable initialization}
	sumTemperature := 0.0;
	sumRain := 0.0;
	averageTemperature := 0.0;
	averageRainfall := 0.0;
	abruptChangeCount := 0;
	heavyRainfallCount := 0;

	{Data input from file}
	writeString("LOAD DATA FROM FILE. ENTER FILE NAME >>");
	filename := readString();
	fileToRead := openFile(filename);

	for i := 1 to DAYS_OF_THE_WEEK do
		avgTemperatures[i] := readRealFromFile(fileToRead);
		avgRainFall[i] := readRealFromFile(fileToRead);
		sumTemperature := sumTemperature + avgTemperatures[i];
		sumRain := sumRain + avgRainFall[i];
	end for

	{Close data file} 
	closeFile(fileToRead);
	
	{Estimated weekly average temperature and rainfall} 
	averageTemperature := sumTemperature / integerToReal(DAYS_OF_THE_WEEK);
	averageRainfall := sumRain / integerToReal(DAYS_OF_THE_WEEK);

	{Data Processing}
	for i := 1 to DAYS_OF_THE_WEEK do
		{Check for abrupt temperature changes}
		if i < DAYS_OF_THE_WEEK then
			if ((avgTemperatures[i] - avgTemperatures[i+1]) >= MAX_TEMP or (avgTemperatures[i] - avgTemperatures[i+1]) <= MIN_TEMP) then
				abruptChangeCount := abruptChangeCount + 1;
				abruptChangeTemperatureDays[abruptChangeCount] := i;
			end if
		end if

	{Check for heavy rain days}
		if avgRainFall[i] >= HEAVY_RAIN_THRESHOLD then
			heavyRainfallCount := heavyRainfallCount + 1;
			heavyRainfallDays[heavyRainfallCount] := i;
		end if
	end for

	{Data output}
	writeString("ESTIMATED WEEKLY AVERAGE TEMPERATURE (CELSIUS):");
	writeReal(averageTemperature);
	writeString("ESTIMATED WEEKLY AVERAGE RAINFALL (MILLIMETERS):");
	writeReal(averageRainfall);

	{Check for weather alerts}
	if abruptChangeCount > 0 or heavyRainfallCount > 0 then
		writeString("WEATHER ALERTS (1-MONDAY, 2-TUESDAY, 3-WEDNESDAY, 4-THURSDAY, 5-FRIDAY, 6-SATURDAY, 7-SUNDAY):");

		{Days with estimated abrupt temperature changes}
		if abruptChangeCount > 0 then
			writeString("Days with abrupt temperature changes:");
			for i := 1 to abruptChangeCount do
				writeInteger(abruptChangeTemperatureDays[i]);
			end for
		end if

		{Estimated heavy rainfall days} 
		if heavyRainfallCount > 0 then
			writeString("Days with heavy rainfall:");
			for i := 1 to heavyRainfallCount do
				writeInteger(heavyRainfallDays[i]);
			end for
		else
			writeString("NO WEATHER ALERTS");
		end if
	end if
end algorithm
