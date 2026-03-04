#pragma once
#include <memory>
#include <string>

enum ResultStatus {
	Intersection,
	Parallel,
	NoIntersection,
	Infinite
};

template <typename T>
class Result {
private:
	ResultStatus _status;
	std::unique_ptr<T> _value;
	std::string _msg;

	Result(const T& value, const ResultStatus& status) {
		_value = std::make_unique<T>(value);
		_status = status;
	}
	
	Result(const std::string& msg, const ResultStatus& status) {
		_msg = msg;
		_status = status;
	}

public:

	~Result() {}

	inline ResultStatus status() noexcept { return _status; };
	inline T value() noexcept { return *_value; };
	inline std::string message() noexcept { return _msg; };

	static Result<T> success(const T& value , const ResultStatus& status) { return Result(value, status); }
	static Result<T> failure(const std::string& msg, const ResultStatus& status) { return Result(msg, status); }
};