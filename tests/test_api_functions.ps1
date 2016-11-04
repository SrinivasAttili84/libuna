# Library API functions testing script
#
# Version: 20160912

$ExitSuccess = 0
$ExitFailure = 1
$ExitIgnore = 77

$TestPrefix = Split-Path -path ${Pwd}.Path -parent
$TestPrefix = Split-Path -path ${TestPrefix} -leaf
$TestPrefix = ${TestPrefix}.Substring(3)

$TestFunctions = "base16_stream base32_stream base64_stream_copy_from base64_stream_copy_to error support unicode_character_copy_from unicode_character_copy_to utf16_stream_copy_from utf16_string_copy_from utf32_stream_copy_from utf32_string_copy_from utf7_stream_copy_from utf8_stream_copy_from utf8_string_copy_from" -split " "

$TestToolDirectory = "..\vs2010\Release"

Function TestAPIFunction
{
	param( [string]$TestFunction, [string[]]$Options, [string]$Profile )

	$TestExecutable = "${TestToolDirectory}\${TestPrefix}_test_${TestFunction}.exe"

	Invoke-Expression ${TestExecutable}
}

Foreach (${TestFunction} in ${TestFunctions})
{
	TestAPIFunction ${TestFunction}

	if (${LastExitCode} -ne ${ExitSuccess})
	{
		Break
	}
}

Exit ${LastExitCode}

