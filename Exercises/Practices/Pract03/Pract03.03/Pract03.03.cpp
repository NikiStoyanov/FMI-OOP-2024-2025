#include <iostream>
#include <fstream>

namespace Constants
{
	constexpr int MAX_NAME_LENGTH = 20;
	constexpr char FILE_NAME[] = "output.dat";
	constexpr char FILTERED_FILE_NAME[] = "filtered.dat";
}

size_t getFileSize(std::ifstream& ifs)
{
	size_t currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);

	size_t size = ifs.tellg();
	ifs.seekg(0, currPos);

	return size;
}

struct JobAd
{
	char companyName[Constants::MAX_NAME_LENGTH];
	uint16_t employeesCount;
	long long salary;
};

JobAd readJobAd()
{
	JobAd jobAd;
	std::cin >> jobAd.companyName;
	std::cin >> jobAd.employeesCount;
	std::cin >> jobAd.salary;

	return jobAd;
}

void writeJobAdsToBinaryFile(size_t count)
{
	std::ofstream ofs(Constants::FILE_NAME, std::ios::binary | std::ios::app);

	if (!ofs.is_open())
	{
		return;
	}

	for (size_t i = 0; i < count; ++i)
	{
		JobAd jobAd = readJobAd();

		ofs.write((const char*)&jobAd, sizeof(JobAd));
	}

	ofs.close();
}

JobAd* getJobAdsFromFile(const char* filename, size_t& count)
{
	std::ifstream ifs(filename, std::ios::binary);

	if (!ifs.is_open())
	{
		return nullptr;
	}

	size_t fileSize = getFileSize(ifs);
	count = fileSize / sizeof(JobAd);

	JobAd* jobAds = new JobAd[count];

	for (size_t i = 0; i < count; ++i)
	{
		ifs.read((char*)&jobAds[i], sizeof(JobAd));
	}

	ifs.close();

	return jobAds;
}

void filterOffers(const char* filePath, long long minSalary)
{
	size_t count = 0;
	JobAd* jobAds = getJobAdsFromFile(filePath, count);

	std::ofstream ofs(Constants::FILTERED_FILE_NAME, std::ios::binary);

	if (!ofs.is_open() || jobAds == nullptr)
	{
		return;
	}

	for (size_t i = 0; i < count; ++i)
	{
		if (jobAds[i].salary >= minSalary)
		{
			ofs.write((const char*)&jobAds[i], sizeof(JobAd));
		}
	}

	delete[] jobAds;
	ofs.close();
}

bool existOffer(const char* filePath, const char* name)
{
	size_t count = 0;
	JobAd* jobAds = getJobAdsFromFile(filePath, count);

	for (size_t i = 0; i < count; ++i)
	{
		if (strcmp(jobAds[i].companyName, name) == 0)
		{
			return true;
		}
	}

	delete[] jobAds;

	return false;
}

int main()
{
	 writeJobAdsToBinaryFile(2);
	 std::ifstream ifs(Constants::FILE_NAME);
	 std::cout << getFileSize(ifs) << std::endl;

	 std::cout << existOffer(Constants::FILE_NAME, "a") << std::endl;
	 std::cout << existOffer(Constants::FILE_NAME, "da") << std::endl;

	 filterOffers(Constants::FILE_NAME, 3);
	 std::ifstream ifs2(Constants::FILTERED_FILE_NAME);
     std::cout << getFileSize(ifs2);
}