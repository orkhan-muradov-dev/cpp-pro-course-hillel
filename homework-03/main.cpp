#include <iostream>
#include <vector>

class FileManager
{
private:
	std::FILE* file_ptr;
	std::string filename;
public:
	explicit FileManager(const char* name, const char* mode) : filename(name), file_ptr(nullptr) {
		file_ptr = fopen(filename.c_str(), mode);
		if (!file_ptr) {
			throw std::runtime_error("Failed to open file " + filename);
		}
		std::cout << "File '" << filename << "' opened successfully in '" << mode << "' mode." << std::endl;
	}
	~FileManager() {
		if (file_ptr){
			if (fclose(file_ptr) == 0) {
				std::cout << "File '" << filename << "' successfully closed." << std::endl;
			}
			else {
				std::cerr << "Error closing file: '" << filename << "'." << std::endl;
			}
		}
	}

	void write(const char* text){
		if (fprintf(file_ptr, "%s\n", text) < 0) {
			std::cerr << "Error writing to file '" << filename << "': \"" << text << "\"" << std::endl;
			return;
		}
		std::cout << "Written to file '" << filename << "': \"" << text << "\"" << std::endl;
	}
};

class Sensor
{
private:
	std::shared_ptr<std::vector<int>> readings;
	std::string sensor_name;
public:
	Sensor(const std::string& name, std::shared_ptr<std::vector<int>> shared_readings = nullptr)
		: sensor_name(name) {
		if (shared_readings) {
			readings = shared_readings;
		}
		else {
			readings = std::make_shared<std::vector<int>>();
		}
		std::cout << "Sensor '" << sensor_name << "' created. Readings are shared (" << readings.use_count() << " owner" << (readings.use_count() > 1 ? "s" : "") << ")." << std::endl;
	}

	void addReading(int value) {
		if (readings) {
			readings->push_back(value);
			std::cout << "Sensor '" << sensor_name << "': Added readings " << value << "." << std::endl;
		}
		else {
			std::cerr << "Sensor '" << sensor_name << "': There is no valid vector to add readings to." << std::endl;
		}
	}

	void printReadings() const {
		if (readings && !readings->empty()) {
			std::cout << "Sensor '" << sensor_name << "' readings (" << readings.use_count() << " owners): [";
			for (size_t i = 0; i < readings->size(); ++i) {
				std::cout << (*readings)[i];
				if (i < readings->size() - 1) {
					std::cout << ", ";
				}
			}
			std::cout << "]" << std::endl;
		}
		else {
			std::cout << "Sensor '" << sensor_name << "': No readings." << std::endl;
		}
	}

	const auto get_name()
	{
		return sensor_name;
	}
};

int main()
{
	std::cout << "----------- Task 1: writing to a file -----------\n" << std::endl;

	try{
		FileManager myFile("note.txt", "w");
		myFile.write("Hello world!");
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n------------------ Task 2: Sensor class ------------------\n" << std::endl
			  << "---------------- Test 1: with shared data ----------------\n" << std::endl;
	
	std::shared_ptr<std::vector<int>> sharedSensorData(new std::vector<int>());
	std::cout << "Created shared readings vector (owner count: " << sharedSensorData.use_count() << ").\n" << std::endl;

	Sensor sensorA("Sensor A", sharedSensorData);
	std::cout << "sharedSensorData.use_count() after creating " << sensorA.get_name() << ": " << sharedSensorData.use_count() << std::endl << std::endl;

	Sensor sensorB("Sensor B", sharedSensorData);
	std::cout << "sharedSensorData.use_count() after creating " << sensorB.get_name() << ": " << sharedSensorData.use_count() << std::endl << std::endl;

	sensorA.addReading(10);
	sensorA.addReading(20);

	std::cout << std::endl;

	sensorB.addReading(30);
	sensorB.addReading(40);

	std::cout << std::endl;

	sensorA.printReadings();
	sensorB.printReadings();

	std::cout << "\nsharedSensorData.use_count() before reset: " << sharedSensorData.use_count() << std::endl;
	sharedSensorData.reset();
	std::cout << "sharedSensorData.use_count() after reset: " << sharedSensorData.use_count() << std::endl

			  << "\n--------------- Test 2: with its own data ---------------\n" << std::endl;

	Sensor sensorC("Sensor C");
	sensorC.addReading(100);
	sensorC.printReadings();

	return 0;
}