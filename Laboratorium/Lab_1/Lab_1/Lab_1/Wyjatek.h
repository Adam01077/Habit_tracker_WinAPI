#pragma once
#include<exception>

class Queue_full : public std::exception {
public:
	const char* what() const noexcept override {
		return "Queue is full! ";
	}
};


class Capacity_warning : public std::exception {
public:
	const char* what() const noexcept override {
		return "Queue need to have a capacity! ";
	}
};

class Queue_empty : public std::exception {
public:
	const char* what() const noexcept override {
		return "Queue is empty. There is nothing to remove! ";
	}
};


class Wrong_type : public std::exception {
public:
	const char* what() const noexcept override {
		return "You can aggregate only int and string! ";
	}
};