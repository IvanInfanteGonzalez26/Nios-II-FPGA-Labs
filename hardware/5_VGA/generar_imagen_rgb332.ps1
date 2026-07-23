Add-Type -AssemblyName System.Drawing

$sourcePath = Join-Path $PSScriptRoot "imagen.jpg"
$outputPath = Join-Path $PSScriptRoot "software\Ej5_vga_hw\imagen_rgb332.h"

$source = [System.Drawing.Image]::FromFile($sourcePath)
$canvas = New-Object System.Drawing.Bitmap 160, 120
$graphics = [System.Drawing.Graphics]::FromImage($canvas)

$graphics.Clear([System.Drawing.Color]::White)
$graphics.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
$graphics.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality

$scale = [Math]::Min(160.0 / $source.Width, 120.0 / $source.Height)
$width = [Math]::Max(1, [int][Math]::Round($source.Width * $scale))
$height = [Math]::Max(1, [int][Math]::Round($source.Height * $scale))
$left = [int]((160 - $width) / 2)
$top = [int]((120 - $height) / 2)

$graphics.DrawImage($source, $left, $top, $width, $height)

$text = New-Object System.Text.StringBuilder
[void]$text.AppendLine("#ifndef IMAGEN_RGB332_H")
[void]$text.AppendLine("#define IMAGEN_RGB332_H")
[void]$text.AppendLine("")
[void]$text.AppendLine("static const unsigned char imagen_rgb332[19200] = {")

for ($y = 0; $y -lt 120; $y++) {
    [void]$text.Append("    ")
    for ($x = 0; $x -lt 160; $x++) {
        $pixel = $canvas.GetPixel($x, $y)
        $rgb332 = (($pixel.R -shr 5) -shl 5) -bor
                  (($pixel.G -shr 5) -shl 2) -bor
                  ($pixel.B -shr 6)
        [void]$text.AppendFormat("0x{0:X2}", $rgb332)
        if (($y -ne 119) -or ($x -ne 159)) {
            [void]$text.Append(",")
        }
    }
    [void]$text.AppendLine()
}

[void]$text.AppendLine("};")
[void]$text.AppendLine("")
[void]$text.AppendLine("#endif")

[System.IO.File]::WriteAllText($outputPath, $text.ToString())

$graphics.Dispose()
$canvas.Dispose()
$source.Dispose()
