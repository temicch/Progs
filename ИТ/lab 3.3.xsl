<?xml version="1.0" encoding="WINDOWS-1251" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template match="/">
<table border="1">
<xsl:for-each select="solar/planet">
<xsl:sort order="ascending" select="number(satellite_number)"/>
<!-- <xsl:if test="dogWeight&lt;10"> -->
<tr bgcolor="#F5F5F5">
<td><xsl:value-of select="planet/@caption"/></td>
<td align="right"><xsl:value-of select="distance"/> <xsl:value-of select="distance/@unit"/></td>
<td><xsl:value-of select="circulation_period"/></td>
</tr>
</xsl:for-each>
</table>
<!-- </xsl:if> 
<xsl:for-each select="tutorial/animals/dogs/dog">
<xsl:sort order="ascending" select="number(dogWeight)"/>
<xsl:if test="dogWeight&gt;15">
<tr bgcolor="#F5F5F5">
<td><xsl:value-of select="dogName"/></td>
<td align="right"><xsl:value-of select="dogWeight"/> <xsl:value-of select="dogWeight/@caption"/></td>
<td><xsl:value-of select="dogColor"/></td>
</tr>
</xsl:if>
</xsl:for-each>