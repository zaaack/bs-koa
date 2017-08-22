const data = `ctx.body
ctx.body=
ctx.status
ctx.status=
ctx.message
ctx.message=
ctx.length=
ctx.length
ctx.type=
ctx.type
ctx.headerSent
ctx.redirect()
ctx.attachment()
ctx.set()
ctx.append()
ctx.remove()
ctx.lastModified=
ctx.etag=`
data.split('\n').map(line => {
  const match = line.match(/ctx\.(\w+)(=?)(\(?\)?)/)
  const name = match[1].replace(/([A-Z])/, (_, c) => '_'+c.toLowerCase())
  const isSet = !!match[2]
  const isMethod = !!match[3]
  if (isSet) {
    console.log(`let set_${name} ctx => Response.set_${name} ctx##response;`)
  } else if (isMethod) {
    console.log(`let ${name} ctx => Response.${name} ctx##response;`)
  } else {
    console.log(`let ${name} ctx => Response.${name} ctx##response;`)
  }
})
