<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.*,java.util.*,java.sql.*"%>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>
 
<html>
<head>
<title>山东大学学生选课管理系统</title>
</head>

<body>
<% request.setCharacterEncoding("UTF-8"); %>
<sql:setDataSource var="snapshot" driver="com.mysql.cj.jdbc.Driver"
     url="jdbc:mysql://localhost:3306/dikzoku?useUnicode=true&serverTimezone=UTC&characterEncoding=utf-8"
     user="root"  password="123456"/>

<c:set var="user_type" value="${param.user_type}"/>
<c:set var="user" value="${param.user}"/>
<c:set var="pwd" value="${param.pwd}"/>
<c:if test="${user_type=='student'}">
	<sql:query dataSource="${snapshot}" var="result">
		select password from student where sid=?<sql:param value="${user}" />
	</sql:query>
</c:if>
<c:if test="${user_type=='teacher'}">
	<sql:query dataSource="${snapshot}" var="result">
		select password from teacher where tid=?<sql:param value="${user}" />
	</sql:query>
</c:if>
<c:if test="${user_type=='admin'}">
	<sql:query dataSource="${snapshot}" var="result">
		select password from admin where aid=?<sql:param value="${user}" />
	</sql:query>
</c:if>

<c:forEach var="row" items="${result.rows}">
	<c:if test="${row.password==pwd}">
		<c:if test="${user_type=='student'}">
			<c:set var="user" value="${param.user}" scope="session"/>
			<script language='javascript'>window.location.href="student.jsp";</script>
		</c:if>
		<c:if test="${user_type=='teacher'}">
			<c:set var="user" value="${param.user}" scope="session"/>
			<script language='javascript'>window.location.href="teacher.jsp";</script>
		</c:if>
		<c:if test="${user_type=='admin'}">
			<c:set var="user" value="${param.user}" scope="session"/>
			<script language='javascript'>window.location.href="admin.jsp";</script>
		</c:if>
	</c:if>
	
	<c:if test="${row.password!=pwd}">
		<script language='javascript'>
			alert('密码错误，请重新输入！');
			window.location.href="index.jsp";
		</script>
	</c:if>
</c:forEach>

<script language='javascript'>
	alert('用户不存在，请联系管理员注册用户！');
	window.location.href="index.jsp";
</script>

</body>
</html>