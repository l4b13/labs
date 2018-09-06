#pragma once

struct sections {
	long Count;
	long blobIndex;
	long bankNameIndex;
	long long startAddress;
	long kind;
	long customSectionNameIndex;
	long accessMode;
} Sections;

struct symbols {
	long Count;
	long sectionINdex;
	long long blobEntryIndex;
	long nameIndex;
} Symbols;

struct sourceFiles {
	long Count;
	long fileNameIndex;
	long sha256hashBytesIndex;
} SourceFiles;

struct sourceTextRanges {
	long Count;
	long sourceFileIndex;
	long position;
	long length;
	long line;
	long column;
} SourceTextRanges;

struct sourceCodePointsCount {
	long Count;
	long long address;
	long sourceOperationRangeIndex;
} SourceCodePointsCount;

struct strings {
	long Count;
	long strLength;
	long *str = new long[strLength];
	void destr() {
		delete[] str;
	};
} Strings;