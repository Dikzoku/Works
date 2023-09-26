<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.*,java.util.*,java.sql.*"%>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>

<!DOCTYPE html>
<html>
   <head>
      <title>山东大学选课管理系统-管理端</title>
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
 		<li><a href="admin.jsp">个人信息</a></li>
  		<li><a href="admin_students.jsp">学生信息</a></li>
  		<li><a href="admin_teachers.jsp">教师信息</a></li>
  		<li><a href="admin_courses.jsp">课程信息</a></li>
  		<li class="active"><a href="admin_departments.jsp">院系信息</a></li>
  		<li style="float:right"><a href="logout.jsp">退出登录</a></li>
		</ul>
		
	<sql:setDataSource var="snapshot" driver="com.mysql.cj.jdbc.Driver"
     url="jdbc:mysql://localhost:3306/dikzoku?useUnicode=true&serverTimezone=UTC&characterEncoding=utf-8"
     user="root"  password="123456"/>
     
     <sql:query dataSource="${snapshot}" var="depart">
     	select * from department
     </sql:query>
     <c:if test="${param.did==null||param.did=='0'}">
     <sql:query dataSource="${snapshot}" var="major">
     	select * from department,major
     	where department.did=major.did
     </sql:query>
     </c:if>
     <c:if test="${param.did!=null&&param.did!='0'}">
        <sql:query dataSource="${snapshot}" var="major">
     	select * from department,major
     	where department.did=major.did 
     		and major.did = ?<sql:param value="${param.did}"/>
     	</sql:query>
     </c:if>
<div class="container">
                          
	<table class="table table-hover">
		<thead>
			<h4>学院信息</h4>
			  <form name="input" action="admin_departments.jsp" method="POST">
 				<c:if test="${param.vi=='0'}">
 					<input type="hidden" name="vi" value="1"/>
 					<input type="submit" value="显示" class="btn btn-default"/>
 				</c:if>
 				<c:if test="${param.vi==null||param.vi=='1'}">
 					<input type="hidden" name="vi" value="0"/>
 					<input type="submit" value="隐藏" class="btn btn-default"/>
 				</c:if>
 				</form>
 			<c:if test="${param.vi=='1'||param.vi==null}">
			<tr>
   		   		<td><c:out value="学院编号"/></td>
   		   		<td><c:out value="学院名称"/></td>
		  	</tr>
		  	</c:if>
		</thead>
		<tbody>
		<c:if test="${param.vi=='1'||param.vi==null}">
		 <c:forEach var="row" items="${depart.rows}">
		  <tr>
   		   <td><c:out value="${row.did}"/></td>
   		   <td><c:out value="${row.dname}"/></td>
		 </c:forEach>
		 </c:if>
		</tbody>
	</table>
	<table class="table table-hover">
		<thead>
			<h4>专业信息</h4>
			    <form name="input" action="admin_departments.jsp" method="POST" >
     			<select name="did" class="form-control" style="text-align:center;width:300px;">
     			<option value="0" selected="selected"><c:out value="所有学院"/></option>
     	 		<c:forEach var="row" items="${depart.rows}">
     	 		
     	 			<c:if test="${row.did==param.did}">
     	  				<option value="${row.did}" selected="selected"><c:out value="${row.dname}"/>(<c:out value="${row.did}"/>)</option>
     	  			</c:if>
     	  			<c:if test="${row.did!=param.did}">
     	  				<option value="${row.did}"><c:out value="${row.dname}"/>(<c:out value="${row.did}"/>)</option>
     	  			</c:if>
     	 		</c:forEach>
   				</select>
     			<button type="submit" class="btn btn-default" style="float:left;">查看该学院专业</button>
     			<c:if test="${param.vi!=null}"><input type="hidden" name="vi" value="${param.vi}"/></c:if>
     			</form>
			<tr>
   		   		<td><c:out value="专业编号"/></td>
   		   		<td><c:out value="专业名称"/></td>
   		   		<td><c:out value="所属学院"/></td>
		  	</tr>
		</thead>
		<tbody>
		 <c:forEach var="row" items="${major.rows}">
		  <tr>
   		   <td><c:out value="${row.mid}"/></td>
   		   <td><c:out value="${row.mname}"/></td>
   		   <td><c:out value="${row.dname}"/></td>
		 </c:forEach>
		</tbody>
	</table>
</div>
     
   </body>
</html>