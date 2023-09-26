<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.*,java.util.*,java.sql.*"%>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>

<!DOCTYPE html>
<html>
   <head>
      <title>山东大学选课管理系统</title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
      <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
      <script src="https://oss.maxcdn.com/libs/respond.js/1.3.0/respond.min.js"></script>
   </head>
   <body>
   <% request.setCharacterEncoding("UTF-8"); %>
      <script src="https://code.jquery.com/jquery.js"></script>
      <script src="js/bootstrap.min.js"></script>
<div class="container" style="width:700px;margin-top:150px;text-align:center">
<img src="sdu.jpg"/>
<h1>山东大学选课管理系统</h1>
</div>      
<div class="container" style="width:500px">
 <form  name="input" action="login.jsp" method="POST">
  <div>
    用户名 <input type="text" class="form-control" name="user" placeholder="请输入用户名">
  </div>
   <div>
    密码 <input type="password" class="form-control" name="pwd" placeholder="请输入密码">
  </div>
  <div style="float:left;width:100px;">
    <select name="user_type" class="form-control" style="text-align:center">
	<option value="student" selected>学生</option>
	<option value="teacher">教师</option>
	<option value="admin">管理员</option>
	</select>
  </div>
  <button type="submit" class="btn btn-default" style="float:right;">登录</button>
</form>
</div>

	</body>
</html>

