param(
    [string]$day,
    [bool]$recompile=$true
)

$path = -join("./day", $day, ".cpp")
if (-not(Test-Path -Path './tmp')) {
    New-Item -Path './tmp' -ItemType Directory | Out-Null
}
if ($recompile) {
    if (Test-Path -Path './tmp/a.exe') {
        Remove-Item ./tmp/a.exe
    }
    if (Test-Path -Path './tmp/main.txt') {
        Remove-Item ./tmp/main.txt
    }
    g++ -std=c++23 -W -Wall -O3 -o './tmp/a.exe' -g $path ./setup.h
}
if (Test-Path -Path './output.txt') {
    Remove-Item ./output.txt
}
if (Test-Path -Path './tmp/a.exe') {
    Get-Content ./input.txt | ./tmp/a.exe | Tee-Object ./output.txt
    Copy-Item $path ./tmp/main.txt
}