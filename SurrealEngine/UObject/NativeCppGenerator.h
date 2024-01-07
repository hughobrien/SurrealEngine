#pragma once

#include "GameFolder.h"
#include "JsonValue.h"

class PackageManager;
class Package;
class UClass;
class UProperty;
class NameString;

class NativeCppGenerator
{
public:
	static void Run();

private:

	struct NativeFunctionDecl
	{
		std::string args;
		std::vector<KnownUE1Games> games;
	};

	struct NativeFunction
	{
		std::string name;
		std::vector<NativeFunctionDecl> decls;
		std::vector<std::pair<KnownUE1Games, int>> versionIndex;
	};

	struct NativeProperty
	{
		std::string name;
		std::string type;
		std::vector<KnownUE1Games> games;
	};

	struct NativeClass
	{
		std::string name;
		std::vector<NativeFunction> funcs;
		std::vector<NativeProperty> props;

		NativeFunction& AddUniqueNativeFunction(const std::string& funcName);
		NativeProperty& AddUniqueNativeProperty(const std::string& propName);

		void ParseClassFunction(const std::string& funcName, const JsonValue& json,  const std::string& game, const int version, const int subversion);
	};

	static void ParseGameNatives(const JsonValue& json, const std::string& game, const int version, const int subversion);
	static void ParseClassNatives(const std::string& className, const JsonValue& json, const std::string& game, const int version, const int subversion);

	static void ParseGameProperties(const JsonValue& json, const std::string& game, const int version, const int subversion);
	static void ParseClassProperties(const std::string& className, const JsonValue& json, const std::string& game, const int version, const int subversion);

	static NativeClass& AddUniqueNativeClass(const std::string& className);

	static std::vector<NativeCppGenerator::NativeClass> classes;
};
