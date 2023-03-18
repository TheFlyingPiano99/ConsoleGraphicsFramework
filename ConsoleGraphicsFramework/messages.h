#pragma once

#include <string>
#include <vector>
#include <random>

class Messages {
public:
	static std::wstring_view getRandomMessage() {
		static std::vector<int> prevIdx;
		int idx = rand() % messages.size();
		while (std::find(prevIdx.begin(), prevIdx.end(), idx) != prevIdx.end()) {
			idx = rand() % messages.size();
		}
		prevIdx.push_back(idx);
		if (prevIdx.size() >= messages.size()) {
			prevIdx.erase(prevIdx.begin());
		}
		return messages[idx];
	}

private:
	static std::vector<std::wstring> messages;
};

std::vector<std::wstring> Messages::messages = {
	L"Szia, Borsó!",
	L"Bababa!",
	L"Szere! <3",
	L"Kiégek! XD",
	L"Nem az a fontos a Jóistennek, hogy kívül mit hordunk, hanem hogy belül mi van.",
	L"Az őszinteség a szellemi élet alapja."
};
