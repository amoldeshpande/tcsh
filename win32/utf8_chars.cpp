#include <unordered_map>
#include <sh.h>

static std::unordered_map<uint32_t,Char> utf8_chars;
static std::unordered_map<Char,uint32_t> reverse_map;

static Char currentIndex;
extern "C" Char get_or_cache_utf8_mb(uint32_t inChar) {
	auto iter = utf8_chars.find(inChar);
	if(iter == utf8_chars.end()) {
		auto ret = utf8_chars.insert({inChar,currentIndex});	
		currentIndex++;
		if(currentIndex == LITERAL ) {
			currentIndex++;
		}
		if (ret.second) {
			reverse_map.insert({ret.first->second,inChar});
			return ret.first->second;
		}
		return 0;
	}
	else {
		return iter->second;
	}
}
extern "C" uint32_t get_cached_utf8_mb(Char index) {

	auto iter = reverse_map.find(index);
	if(iter == reverse_map.end()) {
		return 0x00e29aa0;  //"\U+26A0", Warning sign
	}
	return iter->second;
}
extern "C" void clear_utf8_maps() {
	utf8_chars.clear();
	reverse_map.clear();
}
