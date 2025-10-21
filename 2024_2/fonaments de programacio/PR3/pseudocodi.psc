const
	DAYS_IN_WEEK: integer = 7; {Number of days of the week}
	MAX_RESORTS: integer = 20; {Max. number of ski resorts}
	{Temperature scale conversion constants (CELSIUS/FAHRENHEIT)}
	CELSIUS_FACTOR: real = 0.555; {Round to three decimal places to maintain precision}
	FAHRENHEIT_FACTOR: real = 1.8;
	FAHRENHEIT_OFFSET: real = 32.0;
	HEAVY_RAIN_THRESHOLD: real = 50.0; {Heavy rain threshold in millimeters}
	SNOW_TEMP_CELSIUS_THRESHOLD: real = 0.0; {Temperature below for snow in Celsius degrees}
	SNOW_RAIN_THRESHOLD: real = 10.0; {Minimum rain in millimeters for snow}
end const
{User defined types}
type
	tTemperature = {CELSIUS, FAHRENHEIT}; {Type of temperature scale}
	tWeatherData = record
		temperature: real; {Temperature degree}
		rainAccumulation: real; {Accumulated rainfall in millimeters}
	end record;
	tSkiResort = record
		resortName: string; {Name of the ski resort}
		weekData: vector [DAYS_IN_WEEK] of tWeatherData; {Vector to store weather data}
	end record;
	tSkiResortsTable = record
		resorts: vector [MAX_RESORTS] of tSkiResort; {Ski resorts}
		nResorts: integer; {Number of ski resorts}
	end record;
end type
{Exercise 1}
{Action to load ski resort data from file}
action loadSkiResortsDataFromFile(in filename: string, in scale: tTemperature, out resortsTable: tSkiResortsTable, out isRead: boolean)
	var
		fileToRead: file;
		newResort: tSkiResort;
		i: integer;
		temp: real;
		rain: real;
		resortsTable: tSkiResortsTable;
	end var
	{Open the input file}
	fileToRead := openFile(filename);
	if fileToRead <> NULL then
		{Initialize resorts table}
		resortsTable.nResorts = 0;
		while not isEndOfFile(fileToRead) and resortsTable.nResorts < MAX_RESORTS do
			{Read resort name}
			newResort.resortName := readStringFromFile(fileToRead);
			for i := 1 to DAYS_IN_WEEK do
				{Read temperature, by default Celsius degrees}
				temp := readRealFromFile(fileToRead);
				{Read rainfall in mm}
				rain := readRealFromFile(fileToRead); 
				{Exercise 1.2}
				{If Fahrenheit is needed, convert the temperature}
				if scale = FAHRENHEIT then
					temp := celsiusToFahrenheit(temp);
				end if
				newResort.weekData[i].rainAccumulation := rain;
			end for
			{Exercise 1.3}
			{Add new resort to resorts vector} 
			resortsTable.resorts[resortsTable.nResorts + 1] := newResort;
			resortsTable.nResorts := resortsTable.nResorts + 1;
		end while
		{Close the file}
		closeFile(fileToRead);
		isRead := true;
	else
		isRead := false;
	end if
end action
	{Exercise 2}
function isSnowyWeek(resort: tSkiResort, scale: tTemperature): boolean
	var
		i: integer;
		tempInCelsius: real;
		itWillSnow: boolean;
	end var
	
	itWillSnow := false;
	
	for i := 1 to DAYS_IN_WEEK do
		if scale = CELSIUS then
			tempInCelsius := resort.weekData[i].temperature;
		else
			tempInCelsius := fahrenheitToCelsius(resort.weekData[i].temperature);
		end if
	
		if tempInCelsius <= SNOW_TEMP_CELSIUS_THRESHOLD and resort.weekData[i].rainAccumulation > SNOW_RAIN_THRESHOLD then
			itWillSnow := true;
		end if
		
	end for
	
	return itWillSnow;
end function
	
{Exercise 3} 
action getExtremeTempForecast (in temperature real, out minTemperature real, out maxTemperature real)
	minTemperature := 1000.0;
	maxTemperature := -1000.0;
	for i := 1 to DAYS_IN_WEEK do
        temp := resort.weekData[i].temperature;
        
        if temp < minTemperature then
            minTemperature := temp;
        end if
        
        if temp > maxTemperature then
            maxTemperature := temp;
        end if
    end for
end action

{Exercise 4}
function getResortsWithSnowPrediction(inputTable: tSkiResortsTable, scale: tTemperature): tSkiResortsTable
	var
		outputTable: tSkiResortsTable;
		i: integer;
	end var
	
	{Inicialitzar la taula de sortida}
	outputTable.nResorts := 0;
	
	for i := 1 to inputTable.nResorts do
		if isSnowyWeek(inputTable.resorts[i], scale) then
			outputTable.nResorts := outputTable.nResorts + 1;
			outputTable.resorts[outputTable.nResorts] := inputTable.resorts[i];
		end if
	end for
	
	return outputTable;
end function
	
algorithm SkiResortForecast
	var
		resorts: tSkiResortsTable;
		scale: tTemperature;
		resortsResultsTable: tSkiResortsTable;
		minTemp: real;
		maxTemp: real;
		i: integer;
		filename: string;
		isRead: boolean;
		snowyWeek: bool;
		snowyResorts: tSkiResortsTable;
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
	if isRead then {Data successfully loaded} {Exercise 5}
		{Retrieve and display extreme temperatures forecast}
		writeString("RESULTS:");
		writeString("SKI_STATION MIN_TEMP MAX_TEMP");
		writeString("=============================");
		for i := 1 to resorts.nResorts do
			getExtremeTempForecast(resorts.resorts[i], minTemp, maxTemp);
			writeString(resorts.resorts[i].resortName);
			writeReal(minTemp);
			writeReal(maxTemp);
		end for
		{Exercise 6}
		{Retrieve and display snowy ski resorts}
		snowyResorts := getResortsWithSnowPrediction(resorts, scale);
	
		if snowyResorts.nResorts = 0 then
			write("NO SNOW FORECAST");
		else
			writeString("SNOWY SKI RESORTS");
			writeString("=================");
			for i := 1 to snowyResorts.nResorts do
				writeString(snowyResorts.resorts[i].resortName);
			end for
		end if
	else
		{No data recovered} 
		writeString("NO RESORTS RECOVERED");
	end if
end algorithm