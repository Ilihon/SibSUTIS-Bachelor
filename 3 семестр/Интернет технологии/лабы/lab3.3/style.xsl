<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/solar">
			<HTML>
				<BODY>
    <title> Лабараторная работа 3.3</title>
		<table width="60%" align="center" border="1" cellpadding="2">
			<tr align="center" bgcolor="wheat">
				<td>№</td>
				<td>Название</td>
				<td>Расстояние от Солнца (а.е.)</td>
				<td>Период обращения (г.)</td>
				<td>Период вращения вокруг своей оси (ч.)</td>
				<th>Масса относительно Земли</th>
				<td>Диаметр (км.)</td>
				<td>Количество спутников</td>
			</tr>
			<xsl:for-each select="planet1">
			<xsl:sort order="ascending" select="diametr" data-type="number"/>
			<xsl:sort order="ascending" select="@caption" data-type="text"/>
				<tr align="center">
					<xsl:if test="satellite_number &lt; 1000">
						<xsl:attribute name="bgcolor">mediumpurple</xsl:attribute>
					</xsl:if>
					<xsl:if test="diametr &gt; 25000">
						<xsl:attribute name="bgcolor">blue</xsl:attribute>
					</xsl:if>
					<xsl:if test="diametr &lt; 5000">
						<xsl:attribute name="bgcolor">orange</xsl:attribute>
					</xsl:if>
					<xsl:if test="diametr &lt; 2000">
							<xsl:attribute name="bgcolor">yellow</xsl:attribute>
					</xsl:if>
					<xsl:if test="diametr &gt; 65000">
						<xsl:attribute name="bgcolor">pink</xsl:attribute>
					</xsl:if>
					<xsl:if test="revolution_period &gt; 5000">
						<xsl:attribute name="bgcolor">mediumturquoise</xsl:attribute>
					</xsl:if>
					<xsl:if test="distance &lt; 0.7">
						<xsl:attribute name="bgcolor">mediumseagreen</xsl:attribute>
					</xsl:if>
					<xsl:if test="distance &gt; 39">
						<xsl:attribute name="bgcolor">silver</xsl:attribute>
					</xsl:if>
					<xsl:if test="satellite_number &gt; 16">
						<xsl:attribute name="bgcolor">yellow</xsl:attribute>
					</xsl:if>

					<td><xsl:value-of select="position()"/></td>
					<td><xsl:value-of select="@caption"/></td>
					<td><xsl:value-of select="distance"/></td>
					<td><xsl:value-of select="circulation_period"/></td>
					<td><xsl:value-of select="revolution_period"/></td>
					<th><xsl:value-of select="weight"/></th>
					<td><xsl:value-of select="diametr"/></td>
					<td><xsl:value-of select="satellite_number"/></td>
				</tr>
			</xsl:for-each>
		</table>





		<table width="60%" align="center" border="1" cellpadding="2">
			<tr align="center" bgcolor="wheat">
				<td>№</td>
				<td>Название</td>
				<td>Расстояние от Солнца (а.е.)</td>
				<td>Период обращения (г.)</td>
				<td>Период вращения вокруг своей оси (ч.)</td>
				<th>Масса относительно Земли</th>
				<td>Диаметр (км.)</td>
				<td>Количество спутников</td>
			</tr>
			<xsl:for-each select="planet">
			<xsl:sort order="ascending" select="satellite_number" data-type="number"/>
			<xsl:sort order="ascending" select="@caption" data-type="text"/>
				<tr align="center">
					<xsl:if test="satellite_number &lt; 1000">
						<xsl:attribute name="bgcolor">mediumpurple</xsl:attribute>
					</xsl:if>
					<xsl:if test="diametr &gt; 25000">
						<xsl:attribute name="bgcolor">blue</xsl:attribute>
					</xsl:if>
					<xsl:if test="diametr &lt; 5000">
						<xsl:attribute name="bgcolor">orange</xsl:attribute>
					</xsl:if>
					<xsl:if test="diametr &lt; 2000">
						<xsl:attribute name="bgcolor">yellow</xsl:attribute>
					</xsl:if>
					<xsl:if test="diametr &gt; 65000">
						<xsl:attribute name="bgcolor">pink</xsl:attribute>
					</xsl:if>
					<xsl:if test="revolution_period &gt; 5000">
						<xsl:attribute name="bgcolor">mediumturquoise</xsl:attribute>
					</xsl:if>
					<xsl:if test="distance &lt; 0.7">
						<xsl:attribute name="bgcolor">mediumseagreen</xsl:attribute>
					</xsl:if>
					<xsl:if test="distance &gt; 39">
						<xsl:attribute name="bgcolor">silver</xsl:attribute>
					</xsl:if>
					<xsl:if test="satellite_number &gt; 16">
						<xsl:attribute name="bgcolor">yellow</xsl:attribute>
					</xsl:if>

					<td><xsl:value-of select="position()"/></td>
					<td><xsl:value-of select="@caption"/></td>
					<td><xsl:value-of select="distance"/></td>
					<td><xsl:value-of select="circulation_period"/></td>
					<td><xsl:value-of select="revolution_period"/></td>
					<th><xsl:value-of select="weight"/></th>
					<td><xsl:value-of select="diametr"/></td>
					<td><xsl:value-of select="satellite_number"/></td>
				</tr>
			</xsl:for-each>
		</table>
	 </BODY>
	</HTML>
	</xsl:template>
</xsl:stylesheet>
