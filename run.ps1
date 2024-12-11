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
    if (Test-Path -Path './tmp/a.cpp') {
        Remove-Item ./tmp/a.cpp
    }

    # custom linking (to speed up compilation)
    $setup = Get-Content ./setup.h
    $program = Get-Content $path
    $merged = $setup + $program
    $filtered = $merged | Where-Object { $_ -notmatch '#include "\./setup\.h"' }
    $filtered | Out-File -Encoding ASCII ./tmp/a.cpp
    g++ -std=c++23 -W -Wall -O3 -o './tmp/a.exe' './tmp/a.cpp'
}
if (Test-Path -Path './output.txt') {
    Remove-Item ./output.txt
}
if (Test-Path -Path './tmp/a.exe') {
    Write-Host "compiled" -ForegroundColor Green
    Get-Content ./input.txt | ./tmp/a.exe | Tee-Object ./output.txt
    Copy-Item $path ./tmp/main.txt
} else {
    Write-Host "failed to compile" -ForegroundColor Red
}