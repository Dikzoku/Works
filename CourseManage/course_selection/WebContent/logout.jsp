<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.*,java.util.*,java.sql.*"%>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>山东大学学生选课管理系统</title>
</head>
<body>
<% request.setCharacterEncoding("UTF-8"); %>
	<c:remove var="user"/>
	<script language='javascript'>
		window.location.href="index.jsp";
	</script>
</body>
</html>