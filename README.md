# App móvil: Contador de días, hábitos y metas

Esta propuesta transforma el repositorio en la base de una aplicación móvil centrada en:

- **Dejar hábitos** (por ejemplo: dejar de fumar).
- **Crear hábitos** (por ejemplo: leer 20 min diarios).
- **Objetivos, metas y proyectos** (seguimiento de progreso a largo plazo).
- **Diario personal** con notas diarias.
- **Notificaciones persistentes** por hábito, visibles en pantalla de inicio/barra de notificaciones hasta que el usuario las desactive desde la app.

---

## 1) Visión del producto

Una app que ayuda a la persona a construir constancia. Cada hábito tiene su propio contador de días y su propia notificación persistente para mantener el enfoque durante el día.

### Problemas que resuelve

- Falta de seguimiento diario de hábitos.
- Dificultad para visualizar rachas y progreso real.
- Pérdida de foco en objetivos y proyectos.
- Poco registro personal para entender avances o recaídas.

---

## 2) Funcionalidades principales (MVP)

### 2.1 Gestión de hábitos/objetivos

Cada ítem puede pertenecer a una categoría:

- **Dejar hábito**
- **Crear hábito**
- **Objetivo**
- **Meta**
- **Proyecto**

Campos por ítem:

- `titulo` (obligatorio)
- `descripcion` (opcional)
- `imagen` (opcional, pero mostrada dentro de la app y en la notificación)
- `fecha_inicio`
- `categoria`
- `activo` (sí/no)

### 2.2 Contador de días

- Muestra días transcurridos desde la fecha de inicio.
- Para hábitos diarios: permite marcar cumplimiento por día.
- Cálculo de racha actual y racha máxima.

### 2.3 Diario diario (journal)

- Registro de una nota por día (o varias, según configuración).
- Vinculación opcional con un hábito/objetivo específico.
- Historial por calendario.

### 2.4 Notificaciones persistentes

- Cada hábito activo crea su propia notificación independiente.
- Deben ser persistentes (ongoing) y no descartables por deslizamiento.
- Se eliminan solo si:
  - El usuario desactiva notificaciones del hábito en la app.
  - El hábito se marca como inactivo/finalizado.
- La notificación incluye:
  - Título del hábito.
  - Días acumulados/racha.
  - Imagen asociada (si existe).

---

## 3) Extensiones futuras

- **Alarmas diarias** por hábito (hora configurable, repetición).
- **Widgets personalizables** (1 hábito, lista de hábitos, resumen diario).
- Estadísticas avanzadas (consistencia semanal/mensual).
- Copias de seguridad en nube y sincronización multi-dispositivo.

---

## 4) Diseño técnico sugerido (Android)

> Enfocado a celular y priorizando Android por su soporte robusto de notificaciones persistentes.

### Stack recomendado

- **Kotlin** + **Jetpack Compose**
- **Room** (base de datos local)
- **WorkManager** (tareas periódicas y reprogramación)
- **Foreground Service** para notificaciones realmente persistentes por hábito (según política del sistema)
- **DataStore** para preferencias

### Módulos

- `feature_habits`: creación/edición/listado de hábitos y categorías.
- `feature_journal`: notas diarias.
- `feature_notifications`: gestión de canales, estado persistente y actualización de contenido.
- `core_data`: entidades, DAOs, repositorios.
- `core_ui`: componentes reutilizables.

### Modelo de datos (base)

- `Habit`
  - id, titulo, descripcion, categoria, fechaInicio, imagenUri, activo, notificacionesActivas
- `HabitProgress`
  - id, habitId, fecha, completado
- `JournalEntry`
  - id, fecha, texto, habitId(opcional)
- `Reminder`
  - id, habitId, hora, diasSemana, activo

---

## 5) Reglas de negocio importantes

1. Un hábito activo con notificaciones activas debe tener una notificación vigente.
2. Si se reinicia el dispositivo, la app restaura notificaciones automáticamente.
3. Si el usuario desactiva notificaciones globales desde ajustes del sistema, mostrar aviso en app.
4. El cálculo de días debe considerar zona horaria local y cambio de fecha a medianoche.

---

## 6) UX/UI sugerida

Pantallas mínimas:

1. **Inicio**: resumen del día + hábitos activos + rachas.
2. **Detalle de hábito**: contador, historial, imagen, notas relacionadas.
3. **Crear/editar hábito**: categoría, título, descripción, imagen, notificaciones.
4. **Diario**: calendario y editor de notas.
5. **Ajustes**: permisos de notificación, backup, tema, recordatorios.

Buenas prácticas:

- Onboarding corto para solicitar permisos de notificación de forma contextual.
- Indicadores visuales de progreso (barras, calor mensual, racha).
- Vacíos de estado claros (“Crea tu primer hábito”).

---

## 7) Roadmap recomendado

### Fase 1 (2-4 semanas)

- CRUD de hábitos y categorías.
- Contador de días.
- Diario básico.
- Notificación persistente por hábito (sin alarmas avanzadas).

### Fase 2 (2-3 semanas)

- Alarmas por horario.
- Estadísticas y filtros.
- Mejoras de rendimiento.

### Fase 3 (3-4 semanas)

- Widgets.
- Backup/sync.
- Internacionalización y accesibilidad.

---

## 8) Riesgos y consideraciones

- Restricciones de batería/fabricante pueden afectar persistencia de notificaciones.
- Políticas de foreground services en versiones nuevas de Android.
- Gestión de muchas notificaciones simultáneas (1 por hábito) requiere una UX limpia.

---

## 9) Próximos pasos inmediatos

1. Definir si el MVP será **solo Android**.
2. Crear wireframes de 5 pantallas clave.
3. Inicializar proyecto en Android Studio con arquitectura modular.
4. Implementar primero flujo completo de un hábito: crear → notificar → registrar progreso.
