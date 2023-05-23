#pragma once
#include "Logger.h"

// MARK: - Defines
#define getFirstArg(arg, ...) arg

#define checkIfTrueAndReturn(description, value, equalValue, objName, ...) \
	log(description + objName); \
	if (value == equalValue) return getFirstArg(__VA_ARGS__)

#define checkNullptr(value, objName, ...) \
	checkIfTrueAndReturn(std::string("nullptr finded in "), value, nullptr, objName, __VA_ARGS__)

#define checkNULL(value, objName, ...) \
	checkIfTrueAndReturn(std::string("NULL finded in "), value, NULL, objName, __VA_ARGS__)

static class Utils
{
public:

	template <typename TSource, typename TDestination>
	static void assignIfNotNullRef(TSource^ source, TDestination^ destination)
	{
		if (source != nullptr)
		{
			destination = source;
		}
	}

	template <typename TSource, typename TDestination>
	static void assignIfNotNull(TSource* source, TDestination &destination)
	{
		if (source != nullptr)
		{
			destination = source;
		}
	}
};