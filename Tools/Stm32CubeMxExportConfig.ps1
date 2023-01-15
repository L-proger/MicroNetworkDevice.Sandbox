
#
[string]$fileData = [System.IO.File]::ReadAllText("/home/l/projects/MicroNetworkDevice.Sandbox/F7/Cube/Cube.ioc")


#
$pinRegex = [System.Text.RegularExpressions.Regex]::new("Mcu\.(Pin[\w]+)=P([A-Z][0-9]+)")
$matches = $pinRegex.Matches($fileData)

[string[]]$pinNames = $matches | select {$_.Groups[2]} | select Value

Write-Host "Test"