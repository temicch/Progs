<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
<table border="1">
<TR BGCOLOR = "lightgrey">
	<TH><xsl:value-of select="position()"/></TH>
	<TH>Название</TH>
	<TH>Расстояние до солнца (<xsl:value-of select ="solar/planet/distance/@unit"/>)</TH>
	<TH>Период обращения (<xsl:value-of select = "solar/planet/circulation_period/@unit"/>)</TH>
	<TH>Период обращения вокруг своей оси (<xsl:value-of select = "solar/planet/revolution_period/@unit"/>) </TH>
	<TH>Масса относительно земли (<xsl:value-of select = "solar/planet/weight/@unit"/>)</TH>
	<TH>Диаметр (<xsl:value-of select = "solar/planet/diametr/@unit"/>)</TH>
	<TH>Количество спутников</TH>
</TR>
<xsl:for-each select="solar/planet">
<xsl:sort order="ascending" select="satellite_number" data-type="number"/>
<xsl:sort order="ascending" select="@caption"/>
  <xsl:choose>
	<xsl:when test="(diametr div 2)&lt;10000">
		<tr>
		<xsl:attribute name="BGCOLOR">lightgreen</xsl:attribute>
		<td align="center"><xsl:value-of select="position()+1"/></td>
		<td align="center"><xsl:value-of select="@caption"/></td>
		<td align="center"><xsl:value-of select="distance"/></td>
		<td align="center"><xsl:value-of select="circulation_period"/></td>
		<td align="center"><xsl:value-of select="revolution_period"/></td>
		<td align="center"><xsl:value-of select="weight"/></td>
		<td align="center"><xsl:value-of select="diametr"/></td>
		<td align="center"><xsl:value-of select="satellite_number"/></td>
		</tr>
	</xsl:when>
   <xsl:otherwise>
		<tr>
		<xsl:attribute name="BGCOLOR">lightyellow</xsl:attribute>
		<td align="center"><xsl:value-of select="position()+1"/></td>
		<td align="center"><xsl:value-of select="@caption"/></td>
		<td align="center"><xsl:value-of select="distance"/></td>
		<td align="center"><xsl:value-of select="circulation_period"/></td>
		<td align="center"><xsl:value-of select="revolution_period"/></td>
		<td align="center"><xsl:value-of select="weight"/></td>
		<td align="center"><xsl:value-of select="diametr"/></td>
		<td align="center"><xsl:value-of select="satellite_number"/></td>
		</tr>
   </xsl:otherwise>
  </xsl:choose>
</xsl:for-each>
</table>
</xsl:template>
</xsl:stylesheet>