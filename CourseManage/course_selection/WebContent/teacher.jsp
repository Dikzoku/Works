<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.*,java.util.*,java.sql.*"%>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>

<!DOCTYPE html>
<html>
   <head>
      <title>山东大学选课管理系统-教师端</title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
      <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
      <script src="https://oss.maxcdn.com/libs/respond.js/1.3.0/respond.min.js"></script>
   </head>
   <body>
   <% request.setCharacterEncoding("UTF-8"); %>
      <c:if test="${user==NULL}">
   	  	<script language='javascript'>
			window.location.href="index.jsp";
		</script>
   	  </c:if>
      <script src="https://code.jquery.com/jquery.js"></script>
      <script src="js/bootstrap.min.js"></script>
      
		<ul class="nav nav-tabs">
 		<li class="active"><a href="teacher.jsp">个人信息</a></li>
  		<li><a href="teacher_teach.jsp">授课信息</a></li>
  		<li><a href="teacher_enter_scores.jsp">成绩录入</a></li>
  		<li><a href="teacher_students.jsp">学生名单</a></li>
  		<li style="float:right"><a href="logout.jsp">退出登录</a></li>
		</ul>
		
	<sql:setDataSource var="snapshot" driver="com.mysql.cj.jdbc.Driver"
     url="jdbc:mysql://localhost:3306/dikzoku?useUnicode=true&serverTimezone=UTC&characterEncoding=utf-8"
     user="root"  password="123456"/>
     
     <sql:query dataSource="${snapshot}" var="result">
     	select * from teacher left join department on teacher.did=department.did where tid=?<sql:param value="${user}" />
     </sql:query>
     
<div class="container">                          
	<table class="table table-hover">
		<thead>
			<h4>个人信息</h4>
		</thead>
		<tbody>
		 <c:forEach var="row" items="${result.rows}">
		  <tr>
   		   <td><c:out value="职工号"/></td>
   		   <td><c:out value="${row.tid}"/></td>
		  </tr>
		  <tr>
   		   <td><c:out value="姓名"/></td>
   		   <td><c:out value="${row.name}"/></td>
		  </tr>
		  <tr>
   		   <td><c:out value="性别"/></td>
   		   <td><c:out value="${row.sex}"/></td>
		  </tr>
		  <tr>
   		   <td><c:out value="年龄"/></td>
   		   <td><c:out value="${row.age}"/></td>
		  </tr>
		  <tr>
   		   <td><c:out value="电话"/></td>
   		   <td><c:out value="${row.phone}"/></td>
		  </tr>
		  <tr>
		   <td><c:out value="邮箱"/></td>
   		   <td><c:out value="${row.mail}"/></td>
		  </tr>
		  <tr>
		   <td><c:out value="身份证号"/></td>
   		   <td><c:out value="${row.card_id}"/></td>
		  </tr>
		  <tr>
		   <td><c:out value="学院"/></td>
   		   <td><c:out value="${row.dname}"/></td>
		  </tr>
		 </c:forEach>
		</tbody>
	</table>
	<a class="btn btn-default" href="teacher_upd.jsp" role="button">修改信息或密码</a>
</div>
     
   </body>
</html>