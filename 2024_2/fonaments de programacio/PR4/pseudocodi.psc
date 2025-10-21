const
	DAYS_IN_WEEK: integer := 7; {Number of days of the week}
	MAX_RESORTS: integer := 20; {Max. number of ski resorts}
	{Temperature scale conversion constants (CELSIUS/FAHRENHEIT)}
	CELSIUS_FACTOR: real := 0.555; {Round to three decimal places to maintain precision}
	FAHRENHEIT_FACTOR: real := 1.8;
	FAHRENHEIT_OFFSET: real := 32.0;
	HEAVY_RAIN_THRESHOLD: real := 50.0; {Heavy rain threshold in millimeters}
	SNOW_TEMP_CELSIUS_THRESHOLD: real := 0.0; {Temperature below for snow in Celsius degrees}
	SNOW_RAIN_THRESHOLD: real := 10.0; {Minimum rain in millimeters for snow} {...}
	WIND_THRESHOLD; real := 41.0; {Extreme wind velocity}
	MINIMUM_SNOW_LEVEL: real := 80.0;
	MAXIMUM_SNOW_LEVEL: real := 100.0;
	RAIN_EMERGENCY_DAYS: real := 1;
	WIND_EMERGENCY_DAYS: real := 1;
	SNOW_EMERGENCY_DAYS: real := 3;
end const
{User defined types}
type
	tTemperature := {CELSIUS, FAHRENHEIT}; {Type of temperature scale}
	tWeatherData := record
		scale: tTemperature; {Temperature scale}
		temperature: real; {Temperature degree}
		rainAccumulation: real; {Accumulated rainfall in millimeters}
		windSpeed: real; {wind speed in km/h}
		snowAccumulation: integer; {Accumulated snow in cm}
	end record;
	tSkiResort := record
		resortName: string; {Name of the ski resort}
		weekData: vector [DAYS_IN_WEEK] of tWeatherData; {Vector to store weather data}
		hasRainEmergency: boolean;
		hasWindEmergency: boolean;
		hasSnowEmergency: boolean;
	end record;
	tSkiResortsTable := record
		resorts: vector [MAX_RESORTS] of tSkiResort; {Ski resorts}
		nResorts: integer; {Number of ski resorts}
	end record;
	end type
	{Action to load ski resort data from file}
action loadSkiResortsDataFromFile(in filename: string, in scale: tTemperature, out resortsTable: tSkiResortsTable, out isRead: boolean)
	var
		fileToRead: file;
		newResort: tSkiResort;
		i: integer;
		temperature: real;
		weatherDataTmp: tWeatherData;
	end var
	{Open the input file}
	fileToRead := openFile(filename);
	if fileToRead <> NULL then
		{Exercise 1.1}
		{Initialize resorts table}
		resortsTable.nResorts := 0;
		while not isEndOfFile(fileToRead) and resortsTable.nResorts < MAX_RESORTS do
			{Read resort name}
			newResort.resortName := readStringFromFile(fileToRead);
			for i := 1 to DAYS_IN_WEEK do
				{Read temperature, by default Celsius degrees}
				temperature := readRealFromFile(fileToRead);
				{Read rainfall, wind speed and snow}
				weatherDataTmp.rainAccumulation := readRealFromFile(fileToRead);
				weatherDataTmp.windSpeed := readRealFromFile(fileToRead);
				weatherDataTmp.snowAccumulation := readIntegerFromFile(fileToRead);
				{Set temperature scale}
				weatherDataTmp.scale := scale;
				{If Fahrenheit is needed, convert the temperature}
				if scale := FAHRENHEIT then
					weatherDataTmp.temperature := celsiusToFahrenheit(temperature);
				else
					weatherDataTmp.temperature := temperature;
				end if 
				newResort.weekData[i] := weatherDataTmp;
			end for
			{Add new resort to resorts vector}
			resortsTable.nResorts := resortsTable.nResorts + 1;
			resortsTable.resorts[resortsTable.nResorts] := newResort;
		end while
		{Close the file}
		closeFile(fileToRead);
		isRead := true;
	else
		isRead := false;
	end if
end action
{Exercise 2} 
action getResortsWithEmergency (in: skiResortsTable tSkiResortsTable, out: SkiResortsWithEmergency tSkiResortsTable) 
	var
		SkiResortsWithEmergency: tSkiResortsTable;
		i: integer;
	end var	
	skiResortsWithEmergency.nResorts := 0;
	for i := 1 to skiResortTable.nResorts do
		getExtremeConditions(skiResortsTable.resorts[i])
		if skiResortsTable.resorts[i].hasRainEmergency == true or skiResortsTable.resorts[i].hasWindEmergency == true or skiResortsTable.resorts[i].hasSnowEmergency == true do
			insertOrderedResort(skiResortsTable.resorts[i], skiResortsWithEmergency)
		end if
	end for
end action
{Exercise 2.1} 
action getExtremeConditions (inout resort: tSkiResort)
	var
		rainAccumulationDay: integer := 0;
		windSpeedDay: integer := 0;
		snowAccumulationDays: integer := 0;
		i: integer;
	end var
	for i := 1 to DAYS_IN_WEEK do
		if resort.weekData.rainAccumulation[i] > HEAVY_RAIN_THERSHOLD do
			rainAccumulationDay := rainAccumulationDay + 1;
			if rainAccumulationDay >= RAIN_EMERGENCY_DAYS do
				resort.hasWindEmergency := true;
			end if
		else
			rainAccumulationDay := 0;	
		end if
		if resort.weekData.windSpeed[i] > WIND_THRESHOLD do
			windSpeedDay := windSpeedDay + 1; 
			if windSpeedDayBefore >= WIND_EMERGENCY_DAYS do
				resort.hasWindEmergency := true;
			end if
		else
			windSpeedDay := 0;
		end if
		if isSnowRecommended(resort) == true do
			snowAccumulationDays := snowAccumulationDays +1;
		end if
		snowAccumulationDays := isSnowRecommended(resort);
		if snowAccumulationDays >= SNOW_EMERGENCY_DAYS do
			resort.hasSnowEmergency := true;
		end if	
	end for
end action
{Exercise 2.2} 
function isSnowRecommended (resort: tSkiResort)
	var
		isSnowRecommended: boolean;
	end var
	if resort.snowAccumulation >= MINIMUM_SNOW_LEVEL or resort.snowAccumulation <= MAXIMUM_SNOW_LEVEL do
		isSnowRecommended := false;
	else
		isSnowRecommended .= true;
	end if
	return isSnowRecommended;	
end function
{Exercise 2.3}
action insertOrderedResort(in: resort tSkiResort, inout: resortsTable tSkiResortsTable)
	var
		i,j: integer;
		foundPos: boolean;
	end var
	if not (resortsTable.nResorts == 0 or resort.resortName < resortsTable.resorts.resortName do
		i := 0		
		while i >= resortsTable.nresort and not found do
			if resort.resortName < resortsTable.resorts.resortName do
				foundPos := true;
			else 
				i = i + 1;
			end if
		end while
	else
		i = 0;
	end if
	{move all values a position}
	for j := resortsTable.nResort to i step -1 do
		resortsTable.resorts[j+1] := rwsortsTable.resorts[j]
	end for
	resortsTable.resorts[i] := resort;
	resortsTable.nresort := resortsTable.nresort + 1;
end action
{Exercise 3} 
action writeResorts (inout: skiResortsTable)
	var
		i: integer;
	endvar
	for i := 1 to skiResortsTable.nresorts do
		writeString(skiResortsTable.resorts[i].resortName);
		writeInteger(skiResortsTable.resorts[i].hasRainEmergency);
		writeInteger(skiResortsTable.resorts[i].hasWindEmergency);
		writeInteger(skiResortsTable.resorts[i].hasSnowEmergency);
	end for
endaction
{Exercise 4} 
function isResortInEmergency(resortsWithEmergency tSkiResortsTable, resort string)
	var
		isResortInEmergency: boolean := false;
		i: integer;
		found: boolean;
	end var
	i = 1;
	while i >= resortsWithEmergency.nResorts and not found do
		if resort == resortsWithEmergency.resorts.resortName do
			found = true;
		else
			i = i +1;
		end if
	end while
	return found	
end function
algorithm SkiResortForecast
	var
		resorts: tSkiResortsTable;
		scale: tTemperature;
		resortsResultsTable: tSkiResortsTable;
		filename: string;
		isRead: boolean;
		resortName: string;
		found: boolean;
	end var
	writeString("INPUT DATA");
	{Data input}
	{Input the temperature scale}
	do
		writeString("SELECT TEMPERATURE SCALE (1-CELSIUS, 2-FAHRENHEIT) >>");
		scale := readEnum();
		{Data validation}
		if scale < CELSIUS or scale > FAHRENHEIT then
			writeString("INVALID DATA, TRY AGAIN!");
		end if
	while scale < CELSIUS or scale > FAHRENHEIT;
	{Load data from file}
	writeString("LOAD DATA FROM FILE. ENTER FILE NAME >>");
	filename := readString();
	loadSkiResortsDataFromFile(filename, scale, resorts, isRead);
	if isRead then {Data successfully loaded} {Exercise 2}
		getResortsWithEmergency(resorts, resortsResultTable);
		{Retrieve and display ski resorts with any emergency}
		writeString("RESULTS:");
		writeString("SKI RESORTS WITH EMERGENCIES: R W S");
		writeString("===================================");
		{Exercise 3}
		{Print resorts and their emergencies} 
		if resortsResultsTable.nResorts > 0 then 
			writeResorts(resortsResultTable);
		else
			writeString("NO EMERGENCY SITUATIONS");
		end if
		{Ask for resort to find}
		writeString("SELECT RESORT BY NAME >> ");
		resortName := readString(); {Exercise 4}
		{Search for resort in emergency list} 
		isResortInEmergency(resort, found);
		if found then
			writeString("RESORT IN EMERGENCY LIST");
		else
			writeString("RESORT NOT IN EMERGENCY LIST");
		end if
	else
		{No data recovered}
		writeString("NO SKI RESORTS RECOVERED");
	end if
end algorithm